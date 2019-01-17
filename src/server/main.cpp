#include <iostream>
#include <cstdlib>
#include <memory>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include <microhttpd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne


//#include "ai.h"
//#include "engine.h"
#include "state.h"
#include "server/ServicesManager.hpp"
#include "server/UserService.hpp"
#include "server/VersionService.hpp"
#include "server/CommandService.hpp"
#include "server/SeedService.hpp"
//#include "networkManager.h"

//using namespace ai;
//using namespace engine;
using namespace state;
using namespace std;
//using namespace networkManager;


/*void testRecord(){
  time_t seedtime = time(NULL);
  srand(seedtime);
  PlayerManager* PM = PlayerManager::instance();
  std::shared_ptr<GameState> gameState = std::make_shared<state::GameState>();
  std::vector<Player*> players;
  players.push_back((*PM)[0]);
  // players.push_back((*PM)[1]);
  gameState->SetPlayers(players);
  std::shared_ptr<Moteur> moteur = std::shared_ptr<Moteur>(new Moteur(gameState, true));
  Json::Value intro;
  intro["seedtime"] = to_string(seedtime);
  moteur->AddJsonValue(intro);

  AI_Deep* ai1 = new AI_Deep(gameState, moteur,0);
  // AI_Random* ai2 = new AI_Random (gameState, moteur,1);

  //int entityTurn = 0;
  //int floorNb = 0;
  int i = 0;

  while(i<500){
    if(moteur->GetCommands().size() <= 0){
      ai1->Play();
      if (moteur->GetCommands().size() <= 0){
          moteur->Update(); // le moteur est toujours vide->un ennemi doit être en train de jouer->passer à l'ennemi suivant
      }
    }
    else{
      std::cout << "updating ..." << std::endl;
      moteur->Update();
      //floorNb =  gameState->GetMap()->GetCurrentFloor();
    //  entityTurn =  gameState->GetMap()->GetFloors()[floorNb]->GetCurrentRoom()->GetEntityTurn() ;
    //sleep(0.3);
    }
    i++;
  }
  moteur->~Moteur();
  gameState->~GameState();
}
*/
using namespace std;

class Request {
public:
    struct MHD_PostProcessor *pp = nullptr;
    string data;
    ~Request() {
        if (pp) MHD_destroy_post_processor (pp);
    }
};

// Fonction pour gérer les données imporantes en upload (non implanté ici)
static int
post_iterator(void *cls,
        enum MHD_ValueKind kind,
        const char *key,
        const char *filename,
        const char *content_type,
        const char *transfer_encoding,
        const char *data, uint64_t off, size_t size)
{
    return MHD_NO;
}

// Détruit les données d'une requête
static void
request_completed (void *cls, struct MHD_Connection *connection,
                   void **con_cls, enum MHD_RequestTerminationCode toe)
{
  Request *request = (Request*)*con_cls;
  if (request) {
      delete request;
      *con_cls = nullptr;
  }
}

// Gestionnaire principal
static int
main_handler (void *cls,
          struct MHD_Connection *connection,
          const char *url, //
          const char *method,
          const char *version,
          const char *upload_data, size_t *upload_data_size, void **ptr)
{
    // Données pour une requête (en plusieurs appels à cette fonction)
    Request *request = (Request*)*ptr;

    // Premier appel pour cette requête
    if (!request) {
        request = new Request();
        if (!request) {
            return MHD_NO;
        }
        *ptr = request;
        if (strcmp(method, MHD_HTTP_METHOD_POST) == 0
         || strcmp(method, MHD_HTTP_METHOD_PUT) == 0) {
            request->pp = MHD_create_post_processor(connection,1024,&post_iterator,request);
            if (!request->pp) {
                cerr << "Failed to setup post processor for " << url << endl;
                return MHD_NO;
            }
        }
        return MHD_YES;
    }

    // Cas où il faut récupérer les données envoyés par l'utilisateur
    if (strcmp(method, MHD_HTTP_METHOD_POST) == 0
     || strcmp(method, MHD_HTTP_METHOD_PUT) == 0) {
        MHD_post_process(request->pp,upload_data,*upload_data_size);
        if (*upload_data_size != 0) {
            request->data = upload_data;
            *upload_data_size = 0;
            return MHD_YES;
        }
    }

    HttpStatus status;
    string response;
    try {

        ServicesManager *manager = (ServicesManager*) cls;
        status = manager->queryService(response,request->data,url,method);
    }
    catch(ServiceException& e) {
        status = e.status();
        response = e.what();
        response += "\n";
    }
    catch(exception& e) {
        status = HttpStatus::SERVER_ERROR;
        response = e.what();
        response += "\n";
    }
    catch(...) {
        status = HttpStatus::SERVER_ERROR;
        response = "Unknown exception\n";
    }

    struct MHD_Response *mhd_response;
    mhd_response = MHD_create_response_from_buffer(response.size(),(void *)response.c_str(),MHD_RESPMEM_MUST_COPY);
    if (strcmp(method,MHD_HTTP_METHOD_GET) == 0) {
        MHD_add_response_header(mhd_response,"Content-Type","application/json; charset=utf-8");
    }
    int ret = MHD_queue_response(connection, status, mhd_response);
    MHD_destroy_response(mhd_response);
    return ret;
}

int main(int argc,char* argv[])
{
  SkillManager::instance();
  CardManager::instance();
  PlayerManager::instance();

  time_t seedtime = time(NULL);
  srand(seedtime);
  //Exemple exemple;
  //exemple.setX(53);

  if (argc == 2 and std::string(argv[1]) == "hello")
    cout << "Bonjour le monde !" << endl;
  // if (argc == 2 and std::string(argv[1] )== "record")
  //   testRecord();

  if (argc == 2 and std::string(argv[1] )== "listen"){
    try {
        ServicesManager servicesManager;
       servicesManager.registerService(std::make_unique<VersionService>());

        UserDB userDB;
        CommandDB commandDB;
        // userDB.addUser(std::make_unique<User>(73));
       servicesManager.registerService(std::make_unique<UserService>(std::ref(userDB)));
       servicesManager.registerService(std::make_unique<CommandService>(std::ref(commandDB)));
       servicesManager.registerService(std::make_unique<SeedService>());

        struct MHD_Daemon *d;
        d = MHD_start_daemon(// MHD_USE_SELECT_INTERNALLY | MHD_USE_DEBUG | MHD_USE_POLL,
                MHD_USE_SELECT_INTERNALLY | MHD_USE_DEBUG,
                // MHD_USE_THREAD_PER_CONNECTION | MHD_USE_DEBUG | MHD_USE_POLL,
                // MHD_USE_THREAD_PER_CONNECTION | MHD_USE_DEBUG,
                8080,
                NULL, NULL,
                &main_handler, (void*) &servicesManager,
                MHD_OPTION_NOTIFY_COMPLETED, request_completed, NULL,
                MHD_OPTION_END);
        if (d == NULL)
            return 1;
        cout << "Pressez <entrée> pour arrêter le serveur" << endl;
        (void) getc(stdin);
        MHD_stop_daemon(d);
    }
    catch(exception& e) {
        cerr << "Exception: " << e.what() << endl;
    }
  }

  delete SkillManager::instance();
  delete CardManager::instance();
  delete PlayerManager::instance();
  return 0;
}
