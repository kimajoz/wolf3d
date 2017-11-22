# wolf3d
Inspired by the eponym games of the 90s who was the First Person Shooter, this game allow you to see the raycasting technique. Your aim will be to represent a dynamic view of inside a labyrinth within you can move.

Compile both on Mac and Linux. (with X11)

# How to launch :

- git clone http://github.com/pbillett/wolf3d.git && cd wolf3d
- make re && ./wolf3d [filename.scn]
<code>

      example : ./wolf3d maps/map.scn
      
                ./wolf3d maps/map2.scn
</code>

# Conditions to start:

- This 2 files .spr, and .par needs to exist and be in the same folder as .scn file.
- The .scn file should have same number of elems than lines. (square format / same height as width)
- The .scn file should have 3 or more rows/columns.
- In .scn file: Each character should be, or a number from 0 to 11 included. 0 represented an empty space. And 1 to 11 some textures examples. The delimitor between numbers is ' '. (a single space)

- The .spr file should have 3 numbers per rows. Following this rules:
    - 1: type
    - 2: posX (on map)
    - 3: posY (on map)
- In .spr file: Each character should be, or a number from 0 to 7 included. 0 represented an empty space. And 1 to 7 some textures examples. The delimitor between numbers is ’ ’. (a simple space)

- The .par file should have 3 numbers per rows. Following this rules:
    - 1: posX (on map)
    - 2: posY (on map)
    - 3: rotY (orientation at respawn)

<h4>Here is an example of some valids .scn file:</h4></br>

//Wall_type, Wall_type

<TABLE BORDER="1">
  <TR> 
 <TH> 
    1 1 1 1</br>
    1 0 0 1</br>
    1 0 0 1</br>
    1 1 1 1</br>
 </TH>
 <TH>
    2 2 2 2 2 2 2 2</br>
    2 0 0 0 0 0 0 2</br>
    2 0 0 0 7 7 7 2</br>
    2 0 0 0 7 0 0 2</br>
    2 0 0 0 7 0 7 2</br>
    2 0 0 0 7 0 0 2</br>
    2 0 0 0 0 0 0 2</br>
    2 2 2 2 2 2 0 2</br>
 </TH>
  </TR> 
</TABLE>

<h4>Here is an example of some valids .spr file:</h4></br>

//SprType, PosX, RotY

<TABLE BORDER="1">
  <TR> 
 <TH> 
    1 3 3</br>
 </TH>
 <TH>
    1 3 3</br>
    4 2 5</br>
    4 2 7</br>
 </TH>
  </TR> 
</TABLE>
Note: 4 for type table spr. (as correspond to sprite list in src/w_texture_walls.c file). 2 and 7 for pos x,y on map.

<h4>Here is an example of some valids .par file:</h4></br>

//PosX, PosY, RotY (Start pos)

//PosX, PosY, RotY (End Win pos)

<TABLE BORDER="1">
  <TR> 
 <TH> 
    1 1 0</br>
 </TH>
 <TH>
    1 1 0</br>
    7 8 0</br>
 </TH>
  </TR> 
</TABLE>
Note: 1,1 for x,y as start respawn point. 7,8 for x,y as win point pos on map.

# Shortcut :

<h3>Keyboard:</h3>

- Arrow keys (R/L/Up/Dwn): rotate left/right. Go forward/backard.
- Ctrl(right): fire
- r: reload
- Space: open doors
- 1/4: rays min/max
- 2/3: rays -/+
- Tab: hide minimap
- Escape: quit

Toogles:
- 5: Minimap rays
- 6: Background
- 7: Textures
- 8: Sound

# Compilation possible issues

<h3>Linux</h3>

- Compilation of the Minilibx under Linux needs X11 and Xext dependencies, to install them simply enter this command:
- sudo apt-get install libx11-dev && sudo apt-get install libxext-dev (You should now found all the file under /usr/include/X11/).
- for an eventual problem of use of strlcpy, just comment the line in the file ./minilibx/mlx_xpm.c and uncomment the line just over it that use strcpy.

<h3>Mac</h3>

- Compiltation on Mac should not have any pb issue. As framework OpenGl and framework appKit should be installed by default,
- But if not just use this command line instead of classic make re.
- gcc -o fdf *.c -lm -L libft -lft -L minilibx_macos -L/usr/local/lib/ -I/usr/local/include -lmlx -framework OpenGL -framework AppKit</br>

That's it !
You should now be able to run this project on Mac and Linux.
Enjoy !
