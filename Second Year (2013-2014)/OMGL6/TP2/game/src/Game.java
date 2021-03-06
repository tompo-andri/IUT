/**
 *  This class is the main class, text based adventure game.  Users 
 *  can walk around some scenery. That's all. It should really be extended 
 *  to make it more interesting!
 * 
 *  To play this adventure game, create an instance of this class and call the "play"
 *  method.
 * 
 *  This main class creates and initialises all the others: it creates all
 *  rooms, creates the parser and starts the game.  It also evaluates and
 *  executes the commands that the parser returns.
 * 
 */

public class Game {
    private Parser parser;
    private Room currentRoom;
    private Room exitRoom;
        
    /**
     * Create the game and initialise its internal map.
     */
    public Game()  {
        createRooms();
        parser = new Parser();
    }


    /**
     * Create all the rooms and link their exits together.
     */
    private void createRooms() {
        Room outside, kitchen, fridgedRoom, bedroom, bathroom, toilets, closet, secretStairs, secretDoor, outRoom, sortie;
      
        // create the rooms
        outside = new Room("outside, in front of an enormous door");
        kitchen = new Room("in a little kitchen");
        fridgedRoom = new Room("in a fridged room, care it's cold!");
        bedroom = new Room("in a closy bedroom");
        bathroom = new Room("in a big and classy bathroom");
        toilets = new Room("in a little toilets");
        closet = new Room("in a little closet");
        secretStairs = new Room("on secret stairs");
        secretDoor = new Room("in front of a secret door behind the toilets");
        outRoom = new Room("in front of the exit door");
        sortie = new Room("exit, finally!");
        
        // initialise room exits
        outside.setExits(kitchen, null, null, null);
        kitchen.setExits(bedroom, fridgedRoom, outside, null);
        bedroom.setExits(null, bathroom, kitchen, closet);
        closet.setExits(secretStairs, closet, null, null);
        secretStairs.setExits(null, outRoom, null, closet);
        bathroom.setExits(toilets, null, null, bedroom);
        toilets.setExits(secretDoor, null, bathroom, null);
        outRoom.setExits(sortie, secretDoor, null, secretStairs);
        secretDoor.setExits(null, null, toilets, outRoom);
        sortie.setExits(null, null, outRoom, null);

        currentRoom = outside;  // start game outside
        exitRoom = sortie;
    }


    /**
     *  Main play routine.  Loops until end of play.
     */
    public void play()  {            
        printWelcome();

        // Enter the main command loop.  Here we repeatedly read commands and
        // execute them until the game is over.
                
        boolean finished = false;
        while ((!finished) && (this.currentRoom != this.exitRoom)) {
            Command command = parser.getCommand();
            finished = processCommand(command);
        }
        System.out.println("Thank you for playing.  Good bye.");
    }


    /**
     * Print out the opening message for the player.
     */
    private void printWelcome() {
        System.out.println();
        System.out.println("Welcome to the World of Adventure!");
        System.out.println("World of Adventure is a new, incredibly boring adventure game.");
        System.out.println("Type 'help' if you need help.");
        System.out.println();
        this.printLocation();
    }


    /**
     * Given a command, process (that is: execute) the command.
     * @param command The command to be processed.
     * @return true If the command ends the game, false otherwise.
     */
    private boolean processCommand(Command command) {
        boolean wantToQuit = false;

        if(command.isUnknown()) {
            System.out.println("I don't know what you mean...");
            return false;
        }

        String commandWord = command.getCommandWord();
        if (commandWord.equals("help"))
            printHelp();
        else if (commandWord.equals("go"))
            goRoom(command);
        else if (commandWord.equals("quit"))
            wantToQuit = quit(command);

        return wantToQuit;
    }


    // implementations of user commands:

    /**
     * Print out some help information.
     * Here we print some stupid, cryptic message and a list of the 
     * command words.
     */
    private void printHelp() {
        System.out.println("You are lost. You are alone. You wander");
        System.out.println("around at the university.");
        System.out.println();
        System.out.println("Your command words are:");
        System.out.println("   go quit help");
    }


    /** 
     * Try to go to one direction. If there is an exit, enter
     * the new room, otherwise print an error message.
     */
    private void goRoom(Command command)  {
        if(!command.hasSecondWord()) {
            // if there is no second word, we don't know where to go...
            System.out.println("Go where?");
            return;
        }

        String direction = command.getSecondWord();

        // Try to leave current room.
        Room nextRoom = null;
        if(direction.equals("north")) {
            nextRoom = currentRoom.northExit;
        }
        if(direction.equals("east")) {
            nextRoom = currentRoom.eastExit;
        }
        if(direction.equals("south")) {
            nextRoom = currentRoom.southExit;
        }
        if(direction.equals("west")) {
            nextRoom = currentRoom.westExit;
        }

        if (nextRoom == null) {
        }
        else {
            currentRoom = nextRoom;
            this.printLocation();
        }
    }


    /** 
     * "Quit" was entered. Check the rest of the command to see
     * whether we really quit the game.
     * @return true, if this command quits the game, false otherwise.
     */
    private boolean quit(Command command)   {
        if(command.hasSecondWord()) {
            System.out.println("Quit what?");
            return false;
        }
        else {
            return true;  // signal that we want to quit
        }
    }
    
    public static void main(String[] args) {
    	    Game jeu = new Game();
    	    jeu.play();
    }


    /**
     * Displays the current location and all the available exits
     */
    private void printLocation() {
        System.out.println("You are " + currentRoom.getDescription());

        System.out.print("Exits: ");
        if(currentRoom.northExit != null)
            System.out.print("north ");
        if(currentRoom.eastExit != null)
            System.out.print("east ");
        if(currentRoom.southExit != null)
            System.out.print("south ");
        if(currentRoom.westExit != null)
            System.out.print("west ");
        System.out.println();
    }
    	    
}
