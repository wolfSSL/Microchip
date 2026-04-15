-- tls_server_main.ads
--
-- Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
--
-- This file is part of wolfSSL.
--
-- Contact licensing@wolfssl.com with any questions or comments.
--
-- https://www.wolfssl.com
--
with Tls_Server; pragma Elaborate_All (Tls_Server);

--  SPARK wrapper package around GNAT Library packages.
with SPARK_Sockets; pragma Elaborate_All (SPARK_Sockets);

--  The WolfSSL package.
with WolfSSL; pragma Elaborate_All (WolfSSL);

--  Application entry point for the Ada translation of the
--  tls server v1.3 example in C.
procedure Tls_Server_Main is
   Ssl : WolfSSL.WolfSSL_Type;
   Ctx : WolfSSL.Context_Type;
   L   : SPARK_Sockets.Optional_Socket;
   C   : SPARK_Sockets.Optional_Socket;
begin
   Tls_Server.Run (Ssl, Ctx, L, C);
end Tls_Server_Main;
