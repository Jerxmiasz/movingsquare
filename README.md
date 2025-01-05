## Building the project
for building this project you need to install SFML and PugiXML dependencies and setting them up in the cmake file 
```cmake
# Modifiable values

set (INCLUDE_DIRECTORIES
    "path/to/pugixml/include"
    "path/to/sfml/include"
)
set (LINK_DIRECTORIES
    "path/to/sfml/lib"
    "path/to/pugixml/lib"
)
```
if you are too lazy to do this, you can execute the already build binaries built for Windows x64
# Creating a map
this is an example of the xml file for creating a map
``` xml
  <level>
    <elements>
        <element type="square" x="100" y="180" width="50" height="16" color="130,130,130"  />
        <element type="square" x="200" y="150" width="50" height="16" color="255,0,0"     />
        <element type="square" x="50" y="100" width="50" height="16" color="0,255,0"     />
        <element type="square" x="150" y="50" width="50" height="16" color="0,0,255"    />
        <element type="square" x="250" y="200" width="50" height="16" color="255,255,0"/>
        <element type="circle" x="30" y="200" width="60" height="0" color="0,0,255"  />
    </elements>
</level>
```
And this is the result!
![Captura de pantalla (12)](https://github.com/user-attachments/assets/b77fa078-d06e-43ed-9934-850681e0e76e)
