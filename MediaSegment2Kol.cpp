#include <iostream>
#include <cstring>
using namespace std;

enum tipFormat{
mp3,wav,ogg,flac
};
enum tipKompresija{
x264,Theora, AV1
};


class MediaSegment{
protected:
    char naslov[100];
    char avtor[100];
    int vremetraenje;
    int goleminaMB;
public:
    MediaSegment(char * naslov = "", char * avtor = "",int vremetraenje = 0, int goleminaMB = 0)
    {
        strcpy(this->naslov,naslov);
        strcpy(this->avtor,avtor);
        this->vremetraenje = vremetraenje;
        this->goleminaMB = goleminaMB;
    }
    virtual float price()=0;
};

class AudioRecording: virtual public MediaSegment{
protected:
    tipFormat format;
    short int brKanali;
public:
    AudioRecording(char * naslov = "", char * avtor = "",int vremetraenje = 0, int goleminaMB = 0,
                   tipFormat  format= mp3, short int brKanali = 0)
                   :MediaSegment(naslov,avtor,vremetraenje,goleminaMB)
                   {
                       this->format = format;
                       this->brKanali = brKanali;
                   }

    float price()
    {
        float proizvod = vremetraenje * brKanali;
        if(format == 3)
        {
            proizvod = proizvod * 1.5;
        }
        return proizvod;
    }
    friend ostream& operator<<(ostream & out, AudioRecording &r)
    {
        out<<r.naslov<<" - "<<r.avtor<<" - "<<r.vremetraenje<<
        " - "<<r.goleminaMB<<" - "<<r.price()<<endl;
        return out;
    }
};

class VideoRecording: virtual public MediaSegment{
protected:
    int width;
    tipKompresija kompresija;
public:
    VideoRecording(char * naslov = "", char * avtor = "",int vremetraenje = 0, int goleminaMB = 0,
                   int width = 0, tipKompresija kompresija = x264)
                   :MediaSegment(naslov,avtor,vremetraenje,goleminaMB)
                   {
                       this->width = width;
                       this->kompresija = kompresija;
                   }
    float price()
    {
        int cenaPoSekunda;
        if(width>1920)
        {
            cenaPoSekunda = 170;
        }
        else{
            cenaPoSekunda = 100;
        }
        float totalPrice = cenaPoSekunda * vremetraenje;
        if(kompresija == 0)
        {
            totalPrice = totalPrice * 1.5;
        }
        else if(kompresija == 1)
        {
            totalPrice = totalPrice * 0.9;
        }
        return totalPrice;
    }
     friend ostream& operator<<(ostream & out, VideoRecording &r)
    {
        out<<r.naslov<<" - "<<r.avtor<<" - "<<r.vremetraenje<<
        " - "<<r.goleminaMB<<" - "<<r.width<<" - "<<r.price()<<endl;
        return out;
    }
};

class MusicVideo:public AudioRecording, public VideoRecording{
private:
    char datum[10];
public:
    MusicVideo(char * naslov = "", char * avtor = "",int vremetraenje = 0, int goleminaMB = 0,
      tipFormat  format= mp3, short int brKanali = 0,
         int width = 0, tipKompresija kompresija = x264,
         char * datum = ""):AudioRecording(naslov,avtor,vremetraenje,goleminaMB,format,brKanali),
         VideoRecording(naslov,avtor,vremetraenje,goleminaMB,width,kompresija),
         MediaSegment(naslov,avtor,vremetraenje,goleminaMB)
         {
            strcpy(this->datum,datum);
         }
         float price()
         {
            float totalPrice = AudioRecording::price() + VideoRecording::price();
            if(strcmp(&datum[4],"2010")>0)
            {
             totalPrice = totalPrice * 1.3;
            }
             return totalPrice;
         }
         friend ostream& operator<<(ostream& out, MusicVideo &r)
         {
            out<<r.naslov<<" - "<<r.avtor<<" - "<<r.datum<<
        " - "<<r.vremetraenje<<" - "<<r.price()<<endl;
        return out;
         }
};

float total_price(MediaSegment ** niza, int n)
{
    float total = 0.0;
    for(int i=0;i<n;i++)
    {
        total+=niza[i]->price();
    }
    return total;
}

MusicVideo * cheapest_music_video(MediaSegment ** niza, int n)
{
    MusicVideo * pok;
    MusicVideo * min;
    int flag = 1;
    for(int i=0;i<n;i++)
    {
        pok = dynamic_cast<MusicVideo*>(niza[i]);
        if(pok!=0&&flag == 1)
        {
            min = pok;
            flag = 0;
        }
        if(flag==0&&pok!=0&&min->price()>pok->price())
        {
            min = pok;
        }
    }
    return min;
}


int main()
{

}

