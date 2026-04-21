#include "zaprethandler.h"

ZapretHandler::ZapretHandler() {}

bool ZapretHandler::isActive() {
    return status;
}

void ZapretHandler::start() {
    status = true;
    emit statusChanged(status);
}

void ZapretHandler::stop() {
    status = false;
    emit statusChanged(status);
}
