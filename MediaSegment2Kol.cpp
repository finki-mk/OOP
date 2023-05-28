/*
Да се напише апстрактна класа што репрезентира медија сегмент ( MediaSegment ). За секој медија сегмент се дефинира:

Наслов (низа од најмногу. 100 знаци)
Автор (низа од најмногу 100 знаци)
Времетраење во секунди (позитивен цел број)
Големина на записот во мегабајти (позитивен цел број).
За класата да се имплементираат потребните методи/конструктори за правилно функционирање (според дадената функција main).

Од класата за MediaSegment да се изведат класите за аудио и видео запис.

Класата за аудио запис ( AudioRecording) репрезентира аудио снимка. За аудио записот се чува:

Формат на аудио записот: може да има една од следните вредности: mp3, wav, ogg и flac.
Број на канали - променлива од тип short.
За класата AudioRecording да се имплементираат потребните методи/конструктори за правилно функционирање (според дадената функција main ). 
За класата да се обезбеди функција price што ja пресметува цената на аудио записот. Цената на аудио записот (изразена во евра) се добива на следниот начин:

Се пресметува производ од времетраењето (во секунди) и бројот на канали.
Ако форматот е flac тогаш пресметаниот производ во чекор 1 дополнително се зголемува за 50%
Да се преоптовари операторот << за печатење на информациите за аудио сегментот во форматот:

Наслов - Автор - Времетраeње - големина - цена
Класата за видео запис (VideoRecording) репрезентира видео снимка. За секој видео запис се чува:

Ширина на сликата на видео записот - позитивен цел број
компресија на видео записот - може да има една од следните вредности: х264, Theora, AV1
За класата VideoRecording да се обезбедат потребните методи/конструктори за правилно функционирање (според дадената функција main).

За класата да се обезбеди и функција price што пресметува цена на видео записот. Цената на видео записот (изразена во евра) се пресметува на следниот начин:

Ако ширината е помала или еднаква на 1920 тогаш видео записот чини 100 евра по секунда. Ако ширината е поголема од 1920 тогаш цената е 170 евра по секунда.
Ако компресијата е x264 тогаш пресметаната цена во чекор 1 дополнително се зголемува за 50%. Ако компресијата е Theora, пресметаната цена во чекор 1 се намалува за 10%.
Да се преоптовари операторот << за печатење на информациите за видео записот во формат:

Наслов - Автор - Времетраeње - големина - димензии - цена
Да се креира класа Музичко видео (MusicVideo) што истовремено наследува од класите AudioRecording и VideoRecording. Класата треба чува:

Датум на публикација - низа од знаци во форматот ddmmgggg.
Да се обезбеди метод price за пресметување на цената на музичкото видео. Таа се пресметува како сума од цената на аудио и на видео записот. Ако датумот на публикација е по 2010 година, цената дополнително се зголемува за 30%.

Да се преоптовари операторот << за печатење на информациите за музичкото видео во форматот:

Наслов - Автор - датум на публикација - Времетраeње - цена
Да се имплементира глобална функција total_price што прима низа од покажувачи од тип MediaSegment и нивниот број и пресметува колку чинела продукцијата на сите тие записи.

Да се имплементира глобална функција cheapest_music_video што прима низа од покажувачи од тип MediaSegment и нивниот број и го враќа најевтиното музичко видео во рамките сите записи.
*/
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

