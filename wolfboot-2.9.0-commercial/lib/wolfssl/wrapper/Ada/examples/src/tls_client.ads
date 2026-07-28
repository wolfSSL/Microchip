-- tls_client.ads
--
-- Copyright (C) 2014-2026 wolfSSL Inc.  All rights reserved.
--
-- This file is part of wolfBoot.
--
-- Contact licensing@wolfssl.com with any questions or comments.
--
-- https://www.wolfssl.com
--
 with any questions or comments.
--
-- https://www.wolfssl.com
--
 with any questions or comments.
--
-- https://www.wolfssl.com
--
--  The WolfSSL package.
with WolfSSL; pragma Elaborate_All (WolfSSL);

with SPARK_Sockets; pragma Elaborate_All (SPARK_Sockets);

package Tls_Client with SPARK_Mode is

   procedure Run (Ssl    : in out WolfSSL.WolfSSL_Type;
                  Ctx    : in out WolfSSL.Context_Type;
                  Client : in out SPARK_Sockets.Optional_Socket) with
     Pre  => (not Client.Exists and not
                WolfSSL.Is_Valid (Ssl) and not WolfSSL.Is_Valid (Ctx)),
     Post => (not Client.Exists and not WolfSSL.Is_Valid (Ssl) and
                not WolfSSL.Is_Valid (Ctx)),

     Annotate => (GNATprove, Might_Not_Return);

end Tls_Client;
