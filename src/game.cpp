#include "../includes/game.h"
#include "../includes/fuzzy.h"
const char* bonus_info[7] = {"EXTRA LIFE",
                             "SPACESHIP&BONUSES ACCELERATION",
                             "SCORE MULTIPLIER",
                             "ASTEROIDS SLOWDOWN",
                             "BLINK",
                             "ASTEROIDS ACCELERATION",
                             "DISABLED GUN"};

void Game::play(int height, int width, Settings setts) {
  srand(time(NULL));
  int command = 0, gun_mode = 0, effect = 0, blink = 0;
  char bonussprite = '0', shipsprite = '>', shotsprite = '-';
  int score = setts.score;
  vector<vector<char>> asteroid = {
      {
          '*',
          ' ',
      },
      {
          '*',
          '*',
      },
  };
  Space_Object astpos(10, 10);
  Space_Object shippos(5, height / 2);
  Space_Object shotpos(5, height / 2);
  Space_Object bonuspos(0, 0);
  Bonus bonus(bonussprite, bonuspos);
  Asteroids* asts = new Asteroids(asteroid, astpos, 1 + rand() % 2);
  Shot shot(shotsprite, shotpos);
  Field bord(height, width);
  Spaceship spaceship(setts.hithpoint, shipsprite, shippos);
  Asteroids_Manager manage(bord, 200);
  sethard(&manage);
  Bonus_Manager bonus_manage(bord);
  Gun gun(bord);
  mutex mtx;
  setstatus(0);
  bord.draw_field(0);
  timeout(3);
  setScore(score);
  hard = (hard == 3) ? 0 : hard;
  thread th([&]() {
    while (getstatus() != -1 && getstatus() != 1) {
      manage.asts_manage(1 + hard);
      this_thread::sleep_for(chrono::milliseconds(manage.getVelocity()));
      bord.draw_field(0);
    }
  });
  move(height, width / 2 - 10);
  printw("SCORE: %d\tHP: %d", getScore(), spaceship.getHealt());
  while (1) {
    int prev_score = getScore();
    int prev_health = spaceship.getHealt();
    if (spaceship.getHealt() <= 0) {
      setstatus(-1);
      break;
    }
    command = getch();
    bonus_manage.bonus_manager();
    switch (command) {
      case 'r': {
        if (effect != 6) gun_mode = (gun_mode == 1) ? 0 : 1;
        break;
      }
    }
    if (command) {
      mtx.lock();
      this_thread::sleep_for(chrono::milliseconds(main_velocity));
      spaceship.erase_spaceship();
      spaceship.change_position(command, bord);
      gun_mode = gun.gun_manager(spaceship.getPos(), gun_mode, 0);
      spaceship.draw_spaceship(blink);
      mtx.unlock();
    }
    vector<Asteroids*> all_asts = manage.getAsters();
    vector<Shot*> all_shots = gun.getShots();
    vector<Bonus*> all_bonuses = bonus_manage.getBonuses();
    Fuzzy_Controller fuzzy(30);
    vector<Zone*> all_zones = fuzzy.calculate_distance(&bord, &spaceship);
    for (long unsigned int i = 0; i < all_asts.size(); i++) {
      for (int j = 0; j < asts->getWidth(); j++) {
        for (int k = 0; k < asts->getHeight(); k++) {
          Space_Object offset(j, k);
          // затолкать помеченное в отдельные функции, возможно создрать класс Events
          if(hard == 0) {
            fuzzy.calculate_asteroids(all_zones, all_asts.at(i)->getPos() + offset);
          }
        
          if (all_asts.at(i)->getPos() + offset == spaceship.getPos()) {  // столкновение корабля с астероидом
            all_asts.at(i)->erase_asteroid();
            manage.destruct_asteroid(i);
            spaceship.setHeath(spaceship.getHealt() - 1);
          }

          for (long unsigned int l = 0; l < all_shots.size(); l++) {  // выстрел
            if (all_asts.at(i)->getPos() + offset ==
                all_shots.at(l)->getPos()) {
              all_asts.at(i)->setHeath(all_asts.at(i)->getHealt() - 1);
              all_shots.at(l)->erase_shot();
              setScore(getScore() + 1);
              gun.destruct_shot(l);
              if (all_asts.at(i)->getHealt() == 0) {
                all_asts.at(i)->erase_asteroid();
                manage.destruct_asteroid(i);
                setScore(getScore() + 3);
              }
            }
          }

          for (long unsigned int m = 0; m < all_bonuses.size(); m++) {  // подбор бонуса
            if (all_bonuses.at(m)->getPos() == spaceship.getPos()) {
              effect = all_bonuses.at(m)->set_effect(
                  &spaceship, &manage, &gun, this, sethard(&manage));
              move(height + 1, width / 2 - 10);
              printw("CATCH %s!", bonus_info[effect]);
              all_bonuses.at(m)->erase_bonus();
              bonus_manage.destruct_bonus(m);
            }
          }

        }
      }
    }
    if (hard == 0) {
      mtx.lock();
      this_thread::sleep_for(chrono::milliseconds(main_velocity * 4));
      // int ind = fuzzy.find_optimal_coef(all_zones, &spaceship);
      spaceship.erase_spaceship();
      fuzzy.rules_to_do(all_zones, &spaceship, bord);
      // all_zones.at(0)->setCoefficient(0);
      // int ind = 40;
      // mvaddstr(height + 1, width / 2 - 10, "       ");
      // move(height + 1, width / 2 - 10);
      // printw("%f", all_zones.at(ind)->getCoefficient());
      spaceship.draw_spaceship(blink);
      mtx.unlock();
    }
    if (effect == 4) blink = 1;
    if (getScore() - prev_score != 0 ||
        spaceship.getHealt() - prev_health != 0) {
      mtx.lock();
      move(height, width / 2 - 10);
      // clock_t t1 = clock();
      printw("SCORE: %d\tHP: %d", getScore(), spaceship.getHealt());
      mtx.unlock();
      // move(height+1, width/2-10);
    }
    gun_mode = 0;
  }
  if (getstatus() == -1) {
    th.detach();
    if (effect == 7) {
      setstatus(1);
      bord.draw_field(1);
    }
    Finish finish(bord, filename, setts, *this);
    finish.processing(setts, &bord);
  }
}

int Game::sethard(Asteroids_Manager* asters) {
  int luckybox = 0;
  switch (hard) {
    case 0:
    case 3:
      asters->setVelocity(200);
      setVelocity(30);
      luckybox = rand() % 4;
      break;
    case 1:
      asters->setVelocity(130);
      setVelocity(35);
      luckybox = rand() % 8;
      break;
    case 2:
      asters->setVelocity(70);
      setVelocity(40);
      if (rand() % 4 == 0)
        luckybox = rand() % 4;
      else
        luckybox = 3 + rand() % 8;
      break;
    default:
      break;
  }
  return luckybox;
}
