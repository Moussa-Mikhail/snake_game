#include <optional>
#include <thread>

#include "snake_game_objects.h"

class KeyPoller {
   public:
    std::optional<VelDir> get_dir() const;

    void update_dir();

    void start_polling();

   private:
    std::optional<VelDir> dir;

    std::thread poller_thread;

    static std::optional<VelDir> get_arrow_key();

    static bool is_key_pressed(int vKey);
};