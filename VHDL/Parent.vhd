
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity container is
    port(clk:in std_logic;
  car_ID_out: out integer range 0 to 10;
  car_source_out : out integer range 0 to 4;
  car_target_out : out integer range 0 to 4;
received_drive_from_queue : in std_logic
 );
end entity;

architecture Behavioral of container is

signal Drive,stop,SendInitializeRequest : std_logic;
signal car_ID,server_ID,source,target,positionX,positionY: integer;

begin
car1:entity work.car(Behavioral)
port map (clk=>clk,
Drive=>Drive,
stop=>stop,
SendInitializeRequest=>SendInitializeRequest,
car_ID=>car_ID,
server_ID=>server_ID,
source=>source,
target=>target,
positionX=>positionX,
positionY=>positionY);

server1: entity work.server(Behavioral)
port map (clk=>clk,
  car_ID=>car_ID,
  server_ID =>server_ID,
  car_source =>source,
  car_target=>target,
  send_drive=>Drive,
  send_stop=>stop,
  car_positionX=>positionX,
  car_positionY=>positionY,
  received_drive_from_queue =>received_drive_from_queue,
  car_ID_out =>car_ID_out,
  car_source_out =>car_source_out,
  car_target_out=>car_target_out );
  
 end Behavioral;