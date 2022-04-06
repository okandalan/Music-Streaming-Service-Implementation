#include <iostream>

#include "MusicStream.h"

int main() {
    MusicStream ms;
    
    ms.addProfile("john@doe.com", "john_doe", free_of_charge);
    ms.addProfile("Okan@doe.com", "okan_dalan", free_of_charge);
    ms.addProfile("esin@doe.com", "esin", premium);
    ms.addProfile("vedat@doe.com", "vedat", premium);
    ms.addProfile("ilkan@doe.com", "ilkan", premium);


    ms.addArtist("The Beatles");
    ms.addArtist("The Black Eyes");
    ms.addArtist("Imagine Dragons");

    ms.addAlbum("Please Please Me", 1);
    ms.addAlbum("A Hard Day's Night", 1);
    ms.addAlbum("El Camino", 2);
    ms.addAlbum("Brothers", 2);
    ms.addAlbum("Evolve", 3);
    ms.addAlbum("Origins", 3);


    ms.addSong("Do You Want to Know a Secret", 116, 1);
    ms.addSong("I Saw Here Standing There", 175, 1);
    ms.addSong("Things We Said Today", 155, 2);
    ms.addSong("You Can't Do That", 155, 2);

    ms.addSong("Lonely Boy", 126, 3);
    ms.addSong("Dead and Gone", 120, 3);
    ms.addSong("Toaer", 15, 4);
    ms.addSong("krallar", 1525, 4);

    ms.print();

    return 0;
}
