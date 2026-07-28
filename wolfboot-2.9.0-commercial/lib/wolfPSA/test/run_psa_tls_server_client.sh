#!/usr/bin/env bash
set -euo pipefail

CYAN=$'\033[36m'
YELLOW=$'\033[33m'
RESET=$'\033[0m'
WOLFSSL_DIR="../../wolfssl"

SERVER_LOG="$(mktemp)"
CLIENT_LOG="$(mktemp)"
SERVER_PID=""

cleanup() {
  if [[ -n "${SERVER_PID}" ]]; then
    kill "${SERVER_PID}" >/dev/null 2>&1 || true
    wait "${SERVER_PID}" >/dev/null 2>&1 || true
  fi
  rm -f "${SERVER_LOG}" "${CLIENT_LOG}"
}

trap cleanup EXIT

./psa_tls_server -p 11111 >"${SERVER_LOG}" 2>&1 &
SERVER_PID=$!

CLIENT_OK=0
for _ in $(seq 1 50); do
  if ! kill -0 "${SERVER_PID}" >/dev/null 2>&1; then
    sed "s/^/${CYAN}[SERVER] ${RESET}/" "${SERVER_LOG}"
    echo "server exited before listening" >&2
    exit 1
  fi

  if (
    cd "${WOLFSSL_DIR}" && \
    ../wolfPSA/test/psa_tls_client \
      -h 127.0.0.1 \
      -p 11111 \
      -A certs/ca-ecc-cert.der \
      -c certs/client-ecc-cert.der \
      -k certs/ecc-client-key.der \
      --files-are-der \
      -l ECDHE-ECDSA-AES128-GCM-SHA256 \
      -d
  ) \
    >"${CLIENT_LOG}" 2>&1; then
    CLIENT_OK=1
    break
  fi

  if ! grep -Eq 'Connection refused|tcp connect failed' "${CLIENT_LOG}"; then
    sed "s/^/${CYAN}[SERVER] ${RESET}/" "${SERVER_LOG}"
    sed "s/^/${YELLOW}[CLIENT] ${RESET}/" "${CLIENT_LOG}"
    exit 1
  fi

  sleep 0.1
done

if [[ "${CLIENT_OK}" -ne 1 ]]; then
  sed "s/^/${CYAN}[SERVER] ${RESET}/" "${SERVER_LOG}"
  sed "s/^/${YELLOW}[CLIENT] ${RESET}/" "${CLIENT_LOG}"
  echo "client could not connect to server on port 11111" >&2
  exit 1
fi

wait "${SERVER_PID}"
sed "s/^/${CYAN}[SERVER] ${RESET}/" "${SERVER_LOG}"
sed "s/^/${YELLOW}[CLIENT] ${RESET}/" "${CLIENT_LOG}"
