#include "chain.h"

int main() {
    LogMessage warn_message(WARN, "Warning!");
    LogMessage err_message(ERR, "Error!");
    LogMessage faterr_message(FATERR, "Fatal error! Program terminated");
    LogMessage unknown_message(UNKW, "The unknown message has not been processed...");

    FatalError faterr_handler;
    Error error_handler("error.log");
    Warning warning_handler;
    Unknown unknown_handler;

    faterr_handler.setHandler(&error_handler);
    error_handler.setHandler(&warning_handler);
    warning_handler.setHandler(&unknown_handler);


    faterr_handler.handleMessage(warn_message);
    faterr_handler.handleMessage(err_message);
    faterr_handler.handleMessage(faterr_message);
    faterr_handler.handleMessage(unknown_message);
    
    return 0;
}