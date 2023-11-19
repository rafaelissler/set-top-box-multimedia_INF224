# INF224 - Set-Top Box Multimédia
#### Rafael Issler Rodrigues

### How to use:
Select a function (one of the buttons above the input box), type on the text input box and then click on "Send".

### Commands
- Get object: Prints the multimedia object with the given name on the input box
- Get object of type: Prints the multimedia object with the given type on the input box. Currently, all the objects are of type photo, video or film
- Get object that has: Prints the multimedia objects and groups (alongside with their objects) with a string in their name. The string is given on the input box. Leave the input box empty to get a list of everything.
- Get group: Prints the group with the given name on the input box and all the multimedia objects associated with it
- Play object: Plays the multimedia object with the given name on the input box
- Create object: Creates an object. The input box must be structured following the serialization protocol, using the symbol | as the delimiter
Example 1: photo|family|~/family.png|200|300|
Example 2: video|telecom presentation|C:\Photos\telecom(1).mp4|15|
Example 3: film|oppenheimer 2023|oppenheimer.mov|50|4|10 5 20 15|
- Create group: Creates a group with the given game on the input box
- Add to group: Link a multimedia object to a group. The input box must use the delimiter | and follow the pattern: \<group\>|\<object\>
- Remove object: Removes the multimedia object with the given name on the input box
- Remove group: Removes the group with the given name on the input box
