

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity car is
  Port (
  clk : in std_logic;
  Drive:in std_logic ;
  stop :in std_logic ;
  SendInitializeRequest : out std_logic ;
  car_ID : out integer;
  server_ID:in integer;
  source: out integer range 0 to 4;
  target : out integer range 0 to 4;
  positionX:out integer;
  positionY:out integer 
    );
end car;

architecture Behavioral of car is
signal has_main_server : std_logic :='0'; 
begin
process(clk)
begin
if(has_main_server='0') then
    SendInitializeRequest<='1';
    has_main_server<='1';
    end if;
end process;

end Behavioral;
