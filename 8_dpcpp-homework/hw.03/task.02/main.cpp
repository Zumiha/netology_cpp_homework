#include "observ.h"

int main() {
    Subject obs_subject;
	Subject obs_subject2;
    WarningObserver warningObserver;
    ErrorObserver errorObserver("error_log.txt");
    FatErrorObserver fatalErrorObserver("error_log.txt");

    obs_subject.addObserver(&warningObserver);
    obs_subject.addObserver(&errorObserver);
    obs_subject.addObserver(&fatalErrorObserver);

    obs_subject2.addObserver(&warningObserver);
    obs_subject2.addObserver(&errorObserver);
    obs_subject2.addObserver(&fatalErrorObserver);

    obs_subject.warning("This is a warning message");
    obs_subject.error("This is an error message");
    obs_subject.fatalError("This is a fatal error message");

	obs_subject2.warning("This is a warning message");
    obs_subject2.error("This is an error message");
    obs_subject2.fatalError("This is a fatal error message");

    obs_subject.removeObserver(&warningObserver);
    obs_subject.removeObserver(&errorObserver);
    obs_subject.removeObserver(&fatalErrorObserver);

    obs_subject2.removeObserver(&warningObserver);
    obs_subject2.removeObserver(&errorObserver);
    obs_subject2.removeObserver(&fatalErrorObserver);

	return 0;
}