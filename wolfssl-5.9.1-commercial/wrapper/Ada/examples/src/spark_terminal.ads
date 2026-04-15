-- spark_sockets.ads
--
-- Copyright (C) 2006-2026 wolfSSL Inc.  All rights reserved.
--
-- This file is part of wolfSSL.
--
-- Contact licensing@wolfssl.com with any questions or comments.
--
-- https://www.wolfssl.com
--
with Ada.Command_Line;

--  SPARK wrapper package around the Ada.Command_Line package
--  because this package lacks contracts in the specification
--  file that SPARK can use to verify the context in which
--  subprograms can safely be called.
package SPARK_Terminal with SPARK_Mode is

   subtype Exit_Status is Ada.Command_Line.Exit_Status;

   Exit_Status_Success : Exit_Status renames Ada.Command_Line.Success;
   Exit_Status_Failure : Exit_Status renames Ada.Command_Line.Failure;

   procedure Set_Exit_Status (Status : Exit_Status) with
      Global => null;

   function Argument_Count return Natural;

   function Argument (Number : Positive) return String with
      Pre => Number <= Argument_Count;

end SPARK_Terminal;
