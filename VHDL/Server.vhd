
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;



entity Server is
  Port ( 
  clk:in std_logic ;
  car_ID:in integer range 0 to 10;
  server_ID : out integer ;
  car_source : integer range 0 to 4;
  car_target : integer range 0 to 4;
  send_drive:out std_logic ;
  send_stop: out std_logic ;
  car_positionX:in integer range 0 to 400;
  car_positionY:in integer range 0 to 400;
  received_drive_from_queue : in std_logic 
  );
end Server;

architecture Behavioral of Server is
signal car_positionX_threshold : integer:=100;
signal car_positionY_threshold : integer:=100;
begin
process(clk)
begin
if((car_positionX>=car_positionX_threshold or car_positionY >= car_positionX_threshold) or received_drive_from_queue='1') then
send_drive<='1';
send_stop<='0';
else
send_drive<='0';
send_stop<='1';
end if;

end process;
end Behavioral;
