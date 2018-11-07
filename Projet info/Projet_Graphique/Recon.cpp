<<<<<<< HEAD
#include "Recon.h"
#include <string>
using std::string;

Recon::Recon(int x,int y, int health,int mp, Player* team ):
    Unit(x, y,health, 10, mp,  8,  "ti", 15000, team, 9){
};
=======
#include "Recon.h"
#include <string>
using std::string;

Recon::Recon(int x,int y, int health,int mp, Player* team ):
    Unit(x, y,health, 10, mp,  8,  "ti", team, 9){
};
>>>>>>> d213571adbf17e6bc20bc589b13de732c6dfed5e
