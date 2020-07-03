#include "QuickFingersCore.h"

int main()
{
    QuickFingersCore *session = new QuickFingersCore;
    session->core();
    delete session;
    return 0;
}