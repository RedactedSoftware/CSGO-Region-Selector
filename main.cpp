#include <iostream>
#include <vector>
#include <algorithm>
#include <csignal>

class Region {
public:
    std::string code;
    std::vector<std::string> addresses;
};

#pragma region ipaddresses
Region NAN = {"NAN", {"155.133.253.38", "155.133.253.55", "155.133.253.39", "155.133.253.54", "162.254.193.101", "162.254.193.73", "162.254.193.71", "162.254.193.72", "162.254.193.77", "162.254.193.99", "162.254.193.98", "162.254.193.100"}};
Region NAE = {"NAE", {"162.254.192.70", "162.254.192.67", "162.254.192.72", "162.254.192.68", "162.254.192.69", "162.254.192.66", "162.254.199.170", "162.254.199.178", "162.254.199.180", "162.254.192.73", "162.254.199.173"}};
Region NAW = {"NAW",{"205.196.6.211", "205.196.6.213", "205.196.6.212", "205.196.6.210", "162.254.195.70", "162.254.195.72", "162.254.195.74", "162.254.195.73"}};
Region EUE = {"EUE", {"155.133.226.70", "155.133.226.69", "155.133.226.71", "155.133.226.73", "146.66.155.68", "146.66.155.69", "146.66.155.66", "146.66.155.67", "155.133.230.98", "155.133.252.36", "155.133.252.84", "162.254.196.85", "155.133.248.36", "162.254.196.82", "162.254.196.66"}};
Region EUW = {"EUW", {"162.254.198.102", "162.254.198.103","162.254.198.41", "162.254.198.42", "185.25.182.18", "155.133.248.37", "155.133.248.41", "155.133.248.40"}};
Region EUN = {"EUN",{"162.254.197.36", "155.133.226.72", "155.133.252.86", "155.133.252.89", "155.133.252.38", "155.133.252.52", "185.25.182.51", "155.133.252.53", "185.25.182.50", "155.133.252.37", "162.254.196.70", "155.133.252.88"}};
Region POL = {"POL", {"162.254.197.52", "155.133.226.68", "162.254.197.37", "155.133.230.99", "155.133.230.100", "155.133.230.190", "155.133.252.85", "155.133.230.101", "155.133.252.87"}};
Region SPA = {"SPA", {"155.133.246.34", "155.133.246.50", "185.25.182.19"}};
Region SAM = {"SAM", {"155.133.249.163", "155.133.227.51", "155.133.227.52", "155.133.227.36", "155.133.227.35", "155.133.249.179", "190.217.33.66", "190.217.33.50", "190.217.33.34"}};
Region JP = {"JP", {"146.66.152.37","155.133.245.35", "155.133.239.59"}};
Region HK = {"HK",{"155.133.239.19", "155.133.239.52", "155.133.239.50", "155.133.239.25", "155.133.245.34"}};
Region ALL = {"ALL",{""}};
Region RESET = {"RESET", {""}};
std::vector<Region> regionList = {NAN,NAE,NAW,EUE,EUW,EUN,POL,SPA,SAM,JP,HK};
std::vector<Region> validRegions = {NAN,NAE,NAW,EUE,EUW,EUN,POL,SPA,SAM,JP,HK,ALL,RESET};
std::string selectedRegion;
#pragma endregion ipaddresses

void BlockAllRegionsExcept(const std::string& code) {
    for (int i = 0; (size_t) i < regionList.size(); i++) {
        if (code != regionList[i].code) {
            for (int x = 0; (size_t) x < regionList[i].addresses.size(); x++) {
                std::string ip = regionList[i].addresses[x];
                std::cout << regionList[i].addresses[x] << std::endl;
                popen((((std::string) "sudo iptables -A INPUT -s " += (ip += (std::string) " -j DROP")).c_str()),"r");
                std::cout << ((std::string) "sudo iptables -A INPUT -s " += (ip += (std::string) " -j DROP")).c_str() << std::endl;

            }
        }
    }
}

bool isSuperUser() {
    if (getuid() == 0)
        return true;
    return false;
}

bool RegionExists(const std::string &code) {
    for (int i = 0; (size_t) i < validRegions.size(); i++) {
        if(code == validRegions[i].code)
            return true;
    }
    return false;
}

int main() {
    if (!isSuperUser()) {
        std::cout << "You must execute this program as superuser." << std::endl;
        exit(1);
    }

    std::cout << "Input the region you'd like to queue" << std::endl;
    std::cout << "NAN, NAE, NAW, EUE, EUW, EUN, POL, SPA, SAM, JP, HK, ALL, RESET" << std::endl;
    std::cin >> selectedRegion;

    if(!RegionExists(selectedRegion)) {
        std::cout << "Region does not exist." << std::endl;
        exit(1);
    }

    if(selectedRegion == "RESET") {
        popen("iptables -F", "r");
        exit(0);
    }

    BlockAllRegionsExcept(selectedRegion);
    return 0;
}
