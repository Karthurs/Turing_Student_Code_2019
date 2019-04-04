#include "BigJob.h"

void crawled::getContent(string url)
{
        string command;
        command = "wget -O url_has_been_crawled.txt --tries=1 ";
        command += url;
        system(command.data());
        ifstream fin;
        ofstream fout;
        string  file,file_part;
        int length = 0,len = 0,len1 = 0,location_first = 0,location_end = 0;
	string url_format1 = "href=";
	string url_format2 ;
        fin.open("url_has_been_crawled.txt");
        fout.open("all_different_urls.txt");
        if(fin.is_open() == false)
        {
                cerr << "Can't open file!\n";
                exit(EXIT_FAILURE);
        }
        while(getline(fin,file_part))
        {
                file += file_part;
        }
        location_first = file.find(url_format1);
        if(location_first == string::npos)
        return;
        else
        {
                while(location_first != string::npos)
                {
                        string url_to_be_finded;
			url_format2 = file[location_first+5];
                        location_end = file.find(url_format2,location_first+6);
                        len = location_end-location_first-6;
                        url_to_be_finded = file.substr(location_first+6,len);
                        if(url_to_be_finded.find(_root) != string::npos)
                        {
                                if(url_already_be_crawled.find(url_to_be_finded) == url_already_be_crawled.end())
                                {
                                        fout << url_to_be_finded << endl;
                                        url_to_be_crawled.push(url_to_be_finded);
                                }
                        }
                        if(url_to_be_finded.find("http://") == string::npos)
                        {
                                int loc = url_to_be_finded.find("/");
                                string url_to_be_finded_part;
                                if(loc == 0)
                                url_to_be_finded = _root+url_to_be_finded;
                                else if(loc == string::npos)
                                url_to_be_finded = _root + "/" + url_to_be_finded;
                                else
                                {
                                        url_to_be_finded_part = url_to_be_finded.substr(0,loc);
                                        url_to_be_finded = _root + "/" + url_to_be_finded_part;
                                }
                                if(url_already_be_crawled.find(url_to_be_finded) == url_already_be_crawled.end())
                                {
                                        fout << url_to_be_finded << endl;
                                        url_to_be_crawled.push(url_to_be_finded);
                                }
                        }
                        location_first = file.find(url_format1,location_first+1);
                        url_to_be_finded.erase(0,200);
                }
        }
        return;
}
