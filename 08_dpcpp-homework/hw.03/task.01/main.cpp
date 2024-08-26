#include "logcommand.h"

int main() {
    ConsoleCommand console_command;
    FileCommand file_command("file.txt");

    print(console_command, "Loggin to console...");
    print(file_command, "Loggin to file...");

    
    return 0;
}