-- tls_client_main.adb
--
-- Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
--
-- This file is part of wolfSSL.
--
-- Contact licensing@wolfssl.com with any questions or comments.
--
-- https://www.wolfssl.com
--
with Tls_Client;    pragma Elaborate_All (Tls_Client);
with SPARK_Sockets; pragma Elaborate_All (SPARK_Sockets);
with WolfSSL;       pragma Elaborate_All (WolfSSL);
--  Application entry point for the Ada translation of the
--  tls client v1.3 example in C.
procedure Tls_Client_Main is
   Ssl : WolfSSL.WolfSSL_Type;
   Ctx : WolfSSL.Context_Type;
   C   : SPARK_Sockets.Optional_Socket;
begin
   Tls_Client.Run (Ssl, Ctx, Client => C);
end Tls_Client_Main;
