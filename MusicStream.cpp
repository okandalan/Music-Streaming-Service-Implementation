#include "MusicStream.h"

#include <iostream>

void MusicStream::addProfile(const std::string &email, const std::string &username, SubscriptionPlan plan) {
    /* TODO */
    Profile tmp(email, username, plan);
    profiles.insertAtTheEnd(tmp);      
}

void MusicStream::deleteProfile(const std::string &email) {
    /* TODO */
    Node<Profile> * curr_prof = profiles.getFirstNode();
    int prof_size = profiles.getSize();
    for (int i = 0; i < prof_size; i++) {
        if (curr_prof->data.getEmail() == email) {
            Node<Profile* > * curr_follower = curr_prof->data.getFollowers().getFirstNode();
            int follower_size = curr_prof->data.getFollowers().getSize();
            for (int j = 0; j < follower_size; j++) {
                curr_follower->data->unfollowProfile(&(curr_prof->data));
                curr_follower = curr_follower->next;
            }

            Node<Profile* > * curr_following = curr_prof->data.getFollowings().getFirstNode();
            int following_size = curr_prof->data.getFollowings().getSize();
            for (int k = 0; k < following_size; k++) {
                curr_following->data->getFollowers().removeNode(&(curr_prof->data));
                curr_following = curr_following->next;
            }

            curr_prof->data.getPlaylists().removeAllNodes();
            curr_prof->data.getFollowings().removeAllNodes();
            curr_prof->data.getFollowers().removeAllNodes();

            profiles.removeNode(curr_prof);
            break;

        }

        curr_prof = curr_prof->next;
    }
}

void MusicStream::addArtist(const std::string &artistName) {
    /* TODO */
    artists.insertAtTheEnd(Artist(artistName));
}

void MusicStream::addAlbum(const std::string &albumName, int artistId) {
    /* TODO */
    albums.insertAtTheEnd(Album(albumName));

    Node<Artist> * curr = artists.getFirstNode();
    int size = artists.getSize();
    for (int i = 0; i < size; i++) {
        if (curr->data.getArtistId() == artistId) {
            curr->data.addAlbum(&(albums.getLastNode()->data));
            break;
        }
        curr = curr->next;
    }

}

void MusicStream::addSong(const std::string &songName, int songDuration, int albumId) {
    /* TODO */
    songs.insertAtTheEnd(Song(songName, songDuration));

    Node<Album> * curr_album =  albums.getFirstNode();
    int album_size = albums.getSize();
    for (int i = 0; i < album_size; i++) {
        if (curr_album->data.getAlbumId() == albumId) {
            curr_album->data.addSong(&(songs.getLastNode()->data));
            break;
        }
        curr_album = curr_album->next;
    }

}

void MusicStream::followProfile(const std::string &email1, const std::string &email2) {
    /* TODO */
    Profile * profile1 = NULL;
    Profile * profile2 = NULL;

    Node<Profile> * curr_prof = profiles.getFirstNode();
    int size = profiles.getSize();
    for (int i = 0; i < size; i++) {
        if (curr_prof->data.getEmail() == email1) {
            profile1 = &(curr_prof->data);
        }
        else if (curr_prof->data.getEmail() == email2) {
            profile2 = &(curr_prof->data);
        }
        
        if (profile1 != NULL && profile2 != NULL) break;

        curr_prof = curr_prof->next;
    }

    profile1->followProfile(profile2);
    profile2->getFollowers().insertAtTheEnd(profile1);
}

void MusicStream::unfollowProfile(const std::string &email1, const std::string &email2) {
    /* TODO */
    Profile * profile1 = NULL;
    Profile * profile2 = NULL;

    Node<Profile> * curr_prof = profiles.getFirstNode();
    int size = profiles.getSize();
    for (int i = 0; i < size; i++) {
        if (curr_prof->data.getEmail() == email1) {
            profile1 = &(curr_prof->data);
        }
        else if (curr_prof->data.getEmail() == email2) {
            profile2 = &(curr_prof->data);
        }
        
        if (profile1 != NULL && profile2 != NULL) break;

        curr_prof = curr_prof->next;
    }

    profile1->unfollowProfile(profile2);
    profile2->getFollowers().removeNode(profile1);    

}

void MusicStream::createPlaylist(const std::string &email, const std::string &playlistName) {
    /* TODO */
    Profile * user;

    Node<Profile> * curr_prof = profiles.getFirstNode();
    int size = profiles.getSize();
    for (int i = 0; i < size; i++) {
        if (curr_prof->data.getEmail() == email) {
            user = &(curr_prof->data);
            user->createPlaylist(playlistName);
            break;
        }

        curr_prof = curr_prof->next;
    }
    

}

void MusicStream::deletePlaylist(const std::string &email, int playlistId) {
    /* TODO */
    Profile * user;

    Node<Profile> * curr_prof = profiles.getFirstNode();
    int size = profiles.getSize();
    for (int i = 0; i < size; i++) {
        if (curr_prof->data.getEmail() == email) {
            user = &(curr_prof->data);
            user->deletePlaylist(playlistId);
            break;
        }

        curr_prof = curr_prof->next;
    }    
}

void MusicStream::addSongToPlaylist(const std::string &email, int songId, int playlistId) {
    /* TODO */
    Profile * user;
    Song * added_song;

    Node<Song> * curr_song = songs.getFirstNode();
    int songs_size = songs.getSize();
    for (int j = 0; j < songs_size; j++) {
        if (curr_song->data.getSongId() == songId) {
            added_song = &(curr_song->data);
            break;
        }

        curr_song = curr_song->next;
    }

    Node<Profile> * curr_prof = profiles.getFirstNode();
    int profile_size = profiles.getSize();
    for (int i = 0; i < profile_size; i++) {
        if (curr_prof->data.getEmail() == email) {
            user = &(curr_prof->data);
            user->getPlaylist(playlistId)->addSong(added_song);
            break;
        }

        curr_prof = curr_prof->next;
    } 

}

void MusicStream::deleteSongFromPlaylist(const std::string &email, int songId, int playlistId) {
    /* TODO */
    Profile * user;
    Song * added_song;

    Node<Song> * curr_song = songs.getFirstNode();
    int songs_size = songs.getSize();
    for (int j = 0; j < songs_size; j++) {
        if (curr_song->data.getSongId() == songId) {
            added_song = &(curr_song->data);
            break;
        }

        curr_song = curr_song->next;
    }

    Node<Profile> * curr_prof = profiles.getFirstNode();
    int profile_size = profiles.getSize();
    for (int i = 0; i < profile_size; i++) {
        if (curr_prof->data.getEmail() == email) {
            user = &(curr_prof->data);
            user->getPlaylist(playlistId)->dropSong(added_song);
            break;
        }

        curr_prof = curr_prof->next;
    }     
}

LinkedList<Song *> MusicStream::playPlaylist(const std::string &email, Playlist *playlist) {
    /* TODO */
    Profile * user;
    LinkedList<Song *> advertised_list;

    Node<Profile> * curr_prof = profiles.getFirstNode();
    int size = profiles.getSize();
    for (int i = 0; i < size; i++) {
        if (curr_prof->data.getEmail() == email) {
            user = &(curr_prof->data);
            break;
        }

        curr_prof = curr_prof->next;
    }

    if (user->getPlan() == premium) {
        return playlist->getSongs();
    }
    else {
        advertised_list = playlist->getSongs();
        advertised_list.insertAsEveryKthNode(&(Song().ADVERTISEMENT_SONG),2);
        return advertised_list;
    }     
}

Playlist *MusicStream::getPlaylist(const std::string &email, int playlistId) {
    /* TODO */
    Profile * user;

    Node<Profile> * curr_prof = profiles.getFirstNode();
    int size = profiles.getSize();
    for (int i = 0; i < size; i++) {
        if (curr_prof->data.getEmail() == email) {
            user = &(curr_prof->data);
            break;
        }

        curr_prof = curr_prof->next;
    }

    return user->getPlaylist(playlistId);    
}

LinkedList<Playlist *> MusicStream::getSharedPlaylists(const std::string &email) {
    /* TODO */
    Profile * user;

    Node<Profile> * curr_prof = profiles.getFirstNode();
    int size = profiles.getSize();
    for (int i = 0; i < size; i++) {
        if (curr_prof->data.getEmail() == email) {
            user = &(curr_prof->data);
            break;
        }

        curr_prof = curr_prof->next;
    }

    return user->getSharedPlaylists();    
}

void MusicStream::shufflePlaylist(const std::string &email, int playlistId, int seed) {
    /* TODO */
    getPlaylist(email, playlistId)->shuffle(seed);
    
}

void MusicStream::sharePlaylist(const std::string &email, int playlistId) {
    /* TODO */
    getPlaylist(email, playlistId)->setShared(true);
}

void MusicStream::unsharePlaylist(const std::string &email, int playlistId) {
    /* TODO */
    getPlaylist(email, playlistId)->setShared(false);

}

void MusicStream::subscribePremium(const std::string &email) {
    /* TODO */
    Profile * user;

    Node<Profile> * curr_prof = profiles.getFirstNode();
    int size = profiles.getSize();
    for (int i = 0; i < size; i++) {
        if (curr_prof->data.getEmail() == email) {
            user = &(curr_prof->data);
            break;
        }

        curr_prof = curr_prof->next;
    }

    user->setPlan(premium);    
}

void MusicStream::unsubscribePremium(const std::string &email) {
    /* TODO */
    Profile * user;

    Node<Profile> * curr_prof = profiles.getFirstNode();
    int size = profiles.getSize();
    for (int i = 0; i < size; i++) {
        if (curr_prof->data.getEmail() == email) {
            user = &(curr_prof->data);
            break;
        }

        curr_prof = curr_prof->next;
    }

    user->setPlan(free_of_charge);    
}

void MusicStream::print() const {
    std::cout << "# Printing the music stream ..." << std::endl;

    std::cout << "# Number of profiles is " << this->profiles.getSize() << ":" << std::endl;
    this->profiles.print();

    std::cout << "# Number of artists is " << this->artists.getSize() << ":" << std::endl;
    this->artists.print();

    std::cout << "# Number of albums is " << this->albums.getSize() << ":" << std::endl;
    this->albums.print();

    std::cout << "# Number of songs is " << this->songs.getSize() << ":" << std::endl;
    this->songs.print();

    std::cout << "# Printing is done." << std::endl;
}
