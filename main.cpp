#include <iostream>
#include <stdio.h>
#include <fstream>

std::string commExec(const char* cmd){
    char buffer[128];
    std::string result = "";
    FILE *pipe = popen(cmd, "r");
    if(!pipe)
    	throw std::runtime_error("You have no permission to create file");
    try{
	while(fgets(buffer, sizeof buffer, pipe) != NULL){
	    result += buffer;
	}
    }
    catch(...){
	pclose(pipe);
	throw;
    }
    pclose(pipe);
    return result;
}

void startNetworkScan(){
    std::ofstream dev_list;
    std::string devices = commExec("sudo arp-scan --interface=eth0 --localnet | grep 192.168.56");
    dev_list.open("known_devices");
    if(dev_list.is_open()){
    	dev_list << devices << std::endl;
    }
    dev_list.close();
}

int main(){
    std::cout << "INDIGO-10" << std::endl;
    startNetworkScan();
}
