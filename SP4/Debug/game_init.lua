SP_SIZE_X = 32
SP_SIZE_X = 32
SP_NUM_OF_GRID_X = 3
SP_NUM_OF_GRID_Y = 3

PLAYER_ROTATE_SPEED = 2.5
GRAVITY = -6.0

PLAYER_SIGHT_RANGE = 2500;
PLAYER_REACH_RANGE = 400;
PLAYER_SIGHT_RADIUS = 50;
PLAYER_REACH_RADIUS = 20;

function getIndex(objpos,size,translate)
return ( (objpos / size) - (translate / size));
end

function plusplus(wtf)
return wtf+10;
end