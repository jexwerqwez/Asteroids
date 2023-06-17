#include "../includes/game.h"
#include "../includes/fuzzy.h"
const char *bonus_info[7] = {"EXTRA LIFE",
                             "SPACESHIP&BONUSES ACCELERATION",
                             "SCORE MULTIPLIER",
                             "ASTEROIDS SLOWDOWN",
                             "BLINK",
                             "ASTEROIDS ACCELERATION",
                             "DISABLED GUN"};

void Game::play(int height, int width, Settings setts) {
  srand(time(NULL));
  int command = 0, gun_mode = 0, effect = 0, blink = 0, fuzzy_signal = 0;
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
  Asteroids *asts = new Asteroids(asteroid, astpos, 1 + rand() % 2);
  Shot shot(shotsprite, shotpos);
  Field bord(height, width);
  Spaceship spaceship(setts.hithpoint, shipsprite, 1, 1, shippos);
  Asteroids_Manager manage(bord, 200);
  sethard(&manage);
  Bonus_Manager bonus_manage(bord);
  auto start_time = std::chrono::high_resolution_clock::now();
  Gun gun(bord);
  Fuzzy_Controller fuzzy(30);
  fuzzy.rules_manager();
  fuzzy.rules_prio_manager(fuzzy_coef, fuzzy_dist, fuzzy_prio);
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
      if (effect != 6)
        gun_mode = (gun_mode == 1) ? 0 : 1;
      break;
    }
    }
    // switch (fuzzy_signal) {
    // case 1: {
    //   if (effect != 6)
    //     gun_mode = (gun_mode == 1) ? 0 : 1;
    //   break;
    // }
    // }
    if (command || fuzzy_signal) {
      mtx.lock();
      this_thread::sleep_for(chrono::milliseconds(main_velocity));
      spaceship.erase_spaceship();
      spaceship.change_position(command, bord);
      gun_mode = gun.gun_manager(spaceship.getPos(), gun_mode, 0);
      spaceship.draw_spaceship(blink);
      mtx.unlock();
    }
    vector<Asteroids *> all_asts = manage.getAsters();
    vector<Shot *> all_shots = gun.getShots();
    vector<Bonus *> all_bonuses = bonus_manage.getBonuses();
    vector<Zone *> all_zones = fuzzy.calculate_distance(&bord, &spaceship);
    // char command = '0';
    for (long unsigned int i = 0; i < all_asts.size(); i++) {
      for (int j = 0; j < asts->getWidth(); j++) {
        for (int k = 0; k < asts->getHeight(); k++) {
          Space_Object offset(j, k);
          // затолкать помеченное в отдельные функции, возможно создрать класс
          // Events
          if (hard == 0) {
            fuzzy.calculate_asteroids(&all_zones,
                                      all_asts.at(i)->getPos() + offset,
                                      &spaceship, &bord);
          }

          if (all_asts.at(i)->getPos() + offset ==
              spaceship.getPos()) { // столкновение корабля с астероидом
            all_asts.at(i)->erase_asteroid();
            manage.destruct_asteroid(i);
            spaceship.setHeath(spaceship.getHealt() - 1);
          }

          for (long unsigned int l = 0; l < all_shots.size(); l++) { // выстрел
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

          for (long unsigned int m = 0; m < all_bonuses.size();
               m++) { // подбор бонуса
            if (all_bonuses.at(m)->getPos() == spaceship.getPos()) {
              effect = all_bonuses.at(m)->set_effect(&spaceship, &manage, &gun,
                                                     this, sethard(&manage));
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
      spaceship.erase_spaceship();
      for (auto &zone : all_zones) {
        zone->setPriority(fuzzy.rules_prio_processing(zone->getCoefficient(),
                                                      zone->getDistance()));
      }
      int ind = fuzzy.find_optimal_priority(&all_zones);
      int min_y =
          all_zones.at(ind)->getDistanceY(&spaceship, all_zones.at(ind));
      int min_x =
          all_zones.at(ind)->getDistanceX(&spaceship, all_zones.at(ind));
      int cur_y = all_zones.at(ind)->rejection(
          min_y, &bord, 'Y'); //посчитали отклонение корабля от зоны
      int cur_x = all_zones.at(ind)->rejection(min_x, &bord, 'X');
      double z_x = fuzzy.rules_processing(cur_x, cur_x - spaceship.getHeelX());
      double z_y = fuzzy.rules_processing(cur_y, cur_y - spaceship.getHeelY());
      fuzzy.rules_to_do(&spaceship, &bord, &all_asts, z_x, z_y);

      //   // move(spaceship.getPos().getY(), spaceship.getPos().getX() + 1);
      //   // printw("%d, %lf", cur_y - spaceship.getHeelY(), z_y);
      //   // for (long unsigned int i = 0; i < all_zones.size(); i++) {
      //   //   move(all_zones.at(i)->getPos().getY(),
      //   //        all_zones.at(i)->getPos().getX());
      //   //   printw("%.3lf", all_zones.at(i)->getCoefficient());
      //   // }
      //   spaceship.setHeelX(cur_x);
      //   spaceship.setHeelY(cur_y);
      spaceship.draw_spaceship(blink);
      switch (command) {
      case 'f': {
        FILE *file = fopen("info", "w");
        double coefficients[bord.getFieldHeight()][bord.getFieldWidth()] = {
            0.0};
        for (long unsigned int i = 0; i < all_zones.size(); i++) {
          int x = all_zones.at(i)->getPos().getX();
          int y = all_zones.at(i)->getPos().getY();
          coefficients[y][x] = all_zones.at(i)->getPriority();
        }
        fprintf(file, "Zones and their priorities:");
        for (int i = 0; i < bord.getFieldHeight(); i++) {
          for (int j = 0; j < bord.getFieldWidth(); j++) {
            move(i, j);
            // chtype ch = inch();
            // fprintf(file, "%c", ch & A_CHARTEXT);
            if (coefficients[i][j] == 0)
              fprintf(file, "\t     ");
            else
              fprintf(file, "\t%.3lf", coefficients[i][j]);
          }
          fprintf(file, "\n\n\n\n");
        }

        fprintf(file, "Priority Zone: Priority = %lf\tCoordinates = (%d;%d)\n",
                all_zones.at(ind)->getPriority(),
                all_zones.at(ind)->getPos().getX(),
                all_zones.at(ind)->getPos().getY());
        fprintf(file, "Score = %d\n", score);
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(
            end_time - start_time);
        fprintf(file, "Time: %lld s\n",
                static_cast<long long>(duration.count() % 60));
        fprintf(file, "Fuzzy input:\t Error = (%d;%d), Delta = (%d;%d) \n",
                cur_x, cur_y, cur_x - spaceship.getHeelX(),
                cur_y - spaceship.getHeelY());
        fprintf(file, "Fuzzy output: (%lf; %lf)", z_x, z_y);
        fclose(file);
      }
      }
      mtx.unlock();
    }
    if (effect == 4)
      blink = 1;
    if (getScore() - prev_score != 0 ||
        spaceship.getHealt() - prev_health != 0) {
      mtx.lock();
      move(height, width / 2 - 10);
      printw("SCORE: %d\tHP: %d", getScore(), spaceship.getHealt());

      mtx.unlock();
    }
    // move(height + 2, 1);
    // printw("CHANGEABLE PARAMETERS & KEYS: ZN/ZP %d [1]   PS/NS %d [2]   PM/NM
    // "
    //        "%d [3]",
    //        ZP, PS, PM);
    // move(height + 3, 1);
    // printw("\t\t\t       PB/NB %d [4]   BASIS %d [5]", PB, fuzzy.getBasis());
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

int Game::sethard(Asteroids_Manager *asters) {
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
