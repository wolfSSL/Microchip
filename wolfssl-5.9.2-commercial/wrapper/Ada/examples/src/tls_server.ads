-- tls_server.ads
--
-- Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
--
-- This file is part of wolfSSL.
--
-- Contact licensing@wolfssl.com with any questions or comments.
--
-- https://www.wolfssl.com
--
--  SPARK wrapper package around GNAT Library packages.
with SPARK_Sockets; pragma Elaborate_All (SPARK_Sockets);

--  The WolfSSL package.
with WolfSSL; pragma Elaborate_All (WolfSSL);

package Tls_Server with SPARK_Mode is

   procedure Run (Ssl : in out WolfSSL.WolfSSL_Type;
                  Ctx : in out WolfSSL.Context_Type;
                  L   : in out SPARK_Sockets.Optional_Socket;
                  C   : in out SPARK_Sockets.Optional_Socket) with
      Pre  => (not C.Exists and not L.Exists and not
                  WolfSSL.Is_Valid (Ssl) and not WolfSSL.Is_Valid (Ctx)),
      Post => (not C.Exists and not L.Exists and not
                  WolfSSL.Is_Valid (Ssl) and not WolfSSL.Is_Valid (Ctx));

end Tls_Server;
