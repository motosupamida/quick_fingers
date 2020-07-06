#include "QuickFingersCore.h"

int main()
{
    QuickFingersCore *session = new QuickFingersCore(1200, 800);
    session->core();
    delete session;
    return 0;
}