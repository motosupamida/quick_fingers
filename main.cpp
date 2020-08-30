#include "QuickFingersCore.h"

int main()
{
    QuickFingersCore *session = new QuickFingersCore();
    session->start();
    delete session;
    return 0;
}