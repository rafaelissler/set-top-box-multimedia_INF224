# INF224 - Set-Top Box Multimédia
### Rafael Issler Rodrigues

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

## Notes and answered questions (cpp)

### 2nd Stage
The name of the multimedia object is just an identifier. The object will be played using its path name, which has the name of the file itself.

### 4th Stage
#### "What are these methods called, and how do you declare them?"
They are abstract methods. They are purely virtual methods without an implementation. They are declared by adding a "= 0;" at the end of the function declaration.
#### "If you've done the above as requested, it will no longer be possible to instantiate objects from the base class. Why not?"
A class with at least one abstract method is called an abstract class. These types of classes cannot be instantiated because one of their methods has no declaration and, therefore, don't do anything on their own.

### 5th Stage
#### "What is the characteristic property of object-oriented programming that makes this possible?"
It's the characteristic of polymorphism, as it allows the program to treat objects equally as if they were the base class but with methods that change depending on the derived class.
#### "What is specifically required to do it in C++?"
It's necessary to declare the methods of the base class as "virtual" and mark the respective methods of the derived classes with "override".
#### "What is the type of the array elements: should the array contain objects or pointers to them? Why? Compare with Java."
They should contain pointers, since it's needed for polymorphisme in C++. In java, there is no way for the programmer to use pointers directly, but all objects are treated as a pointer to the object.

### 7th Stage
#### "Which of the previously written classes must be modified so that there is no memory leak when the objects are destroyed?"
The Film class must be modified. This is due to the fact that the array "chapters" of the class is instantiated with a "new" operation.
#### "Copying objects can also be a problem when they have instance variables that are pointers. What's the problem and what are the solutions?"
The problem would be that a shallow copy would copy only the pointer, which would point to the same object. This can cause errors if the original object deletes the pointed variable and then the copy tries to delete it as well. To solve it, we can create a copy constructor for the class to copy the contents of the array itself (deep copy) or overload the operator of copy.

### 8th Stage
#### "We also remind you that the object list must in fact be a list of object pointers. Why is this? Compare with Java."
We use a list of object pointers because we don't want the objects themselves to be destroyed when the group is destroyed. If we use pointers to objects, the original objects will remain unchanged. Also, if the objects change in any way, the objects in the group would change as well. In java, all objects are treated as pointers, so this question would not be a concern.

### 10th Stage

The manager is able to:

- Create a group or any multimedia object
- Read from an input stream using readFromFile
- Send the attributes of a particular (or many) objects and groups using printMultimedia, printAllMultimedia, printType, printContains and printGroup
- Remove a multimedia object or group using removeMultimedia and removeGroup
- Play a multimedia object using play

#### "The previous methods ensure database consistency, because when an object is created, it is added to the appropriate table. However, this won't be the case if you create an object directly with new (it won't belong to any table). How can we prevent this, so that only the class used to manipulate objects can create new ones?""
We can make it so the constructors of the media classes are private and make the manager class a friend. With that, a factory can be implemented in the managaer class.

### 11th Stage
A file called "commands.h" was created to store the lambda variables used for the commands of the server. These commands are explained in the first section of this README.

### 12th Stage
The serialization and de-serialization of groups was implemented.

### 13th Stage
The try-catch alternative wasn't used to deal with errors. Instead, methods will return a different value when they're faced with an error. These include:

- Manager::createGroup will return a nullptr if a group with same name already exists
- Manager::createPhoto, Manager::createVideo, Manager::createFilm will return a blank version of the object with no name if an object with same name already exists
- Manager::createMultimedia will return the same as the above or a nullptr if the type of multimedia object given wasn't recognized
- Manager:getObjectByName, Manager::getGroupByName will return a nullptr if the group or object weren't found

However, methods that will print an object to a stream won't deal with errors themselves. They will simply send the error message to the client (Usually, when they can't find an object requested by the client).

## Notes and answered questions (swing)
### 1st stage
#### "Launch your program, click several times on the first two buttons, then resize the window. What can you see?"
There is no scrolling implemented for the text box.

## General notes
The name of the multimedia object is just an identifier. The object will be played using its path name, which has the name of the file itself.

A default set of multimedia objects, stored in "_objects.txt", will be read and loaded at the start of execution.

The message delimiter | was chosen to allow spacebar in the name of the files. Now, the character | is not allowed in the name and path of an object.