#include "Profile.h"

Profile::Profile(const std::string &email, const std::string &username, SubscriptionPlan plan) {
    this->email = email;
    this->username = username;
    this->plan = plan;
}

const std::string &Profile::getUsername() const {
    return this->username;
}

const std::string &Profile::getEmail() const {
    return this->email;
}

SubscriptionPlan Profile::getPlan() const {
    return this->plan;
}

LinkedList<Playlist> &Profile::getPlaylists() {
    return this->playlists;
}

LinkedList<Profile *> &Profile::getFollowings() {
    return this->following;
}

LinkedList<Profile *> &Profile::getFollowers() {
    return this->followers;
}

void Profile::setPlan(SubscriptionPlan plan) {
    this->plan = plan;
}

void Profile::followProfile(Profile *profile) {
    /* TODO */
    following.insertAtTheEnd(profile);
}

void Profile::unfollowProfile(Profile *profile) {
    /* TODO */
    following.removeNode(profile);
}

void Profile::createPlaylist(const std::string &playlistName) {
    /* TODO */
    Playlist new_playlist(playlistName);
    playlists.insertAtTheEnd(new_playlist);
}

void Profile::deletePlaylist(int playlistId) {
    /* TODO */
    Node<Playlist> *curr = playlists.getFirstNode();
    int size = playlists.getSize();
    for (int i = 0; i < size; i++) {
        if (curr->data.getPlaylistId() == playlistId) {
            curr->data.getSongs().removeAllNodes();
            playlists.removeNode(curr);
            break;
        }
        curr = curr->next;
    }
}

void Profile::addSongToPlaylist(Song *song, int playlistId) {
    /* TODO */
    Node<Playlist> *curr = playlists.getFirstNode();
    int size = playlists.getSize();
    for (int i = 0; i < size; i++) {
        if (curr->data.getPlaylistId() == playlistId) {
            curr->data.addSong(song);
            break;
        }
        curr = curr->next;
    }    
}

void Profile::deleteSongFromPlaylist(Song *song, int playlistId) {
    /* TODO */
    Node<Playlist> *curr = playlists.getFirstNode();
    int size = playlists.getSize();
    for (int i = 0; i < size; i++) {
        if (curr->data.getPlaylistId() == playlistId) {
            curr->data.dropSong(song);
            break;
        }
        curr = curr->next;
    }    
}

Playlist *Profile::getPlaylist(int playlistId) {
    /* TODO */
    Node<Playlist> *curr = playlists.getFirstNode();
    int size = playlists.getSize();
    for (int i = 0; i < size; i++) {
        if (curr->data.getPlaylistId() == playlistId) {
            return &(curr->data);
        }
        curr = curr->next;
    }

    return NULL;    
}

LinkedList<Playlist *> Profile::getSharedPlaylists() {
    /* TODO */
    LinkedList<Playlist *> shared_lists;

    Node<Profile *> *curr_prof = following.getFirstNode();
    int following_size = following.getSize();
    for (int i = 0; i < following_size; i++) {
        int following_playlist_size = curr_prof->data->playlists.getSize();
        Node<Playlist> * curr_list = curr_prof->data->playlists.getFirstNode();
        for (int j = 0; j < following_playlist_size; j++) {
            if (curr_list->data.isShared()) {
                shared_lists.insertAtTheEnd(&(curr_list->data));
            }
            curr_list = curr_list->next;
        }
        curr_prof = curr_prof->next;
    }

    return shared_lists;
}

void Profile::shufflePlaylist(int playlistId, int seed) {
    /* TODO */
    Node<Playlist> *curr = playlists.getFirstNode();
    int size = playlists.getSize();
    for (int i = 0; i < size; i++) {
        if (curr->data.getPlaylistId() == playlistId) {
            curr->data.getSongs().shuffle(seed);
            break;
        }
        curr = curr->next;
    }     
    
}

void Profile::sharePlaylist(int playlistId) {
    /* TODO */
    Node<Playlist> *curr = playlists.getFirstNode();
    int size = playlists.getSize();
    for (int i = 0; i < size; i++) {
        if (curr->data.getPlaylistId() == playlistId) {
            curr->data.setShared(true);
            break;
        }
        curr = curr->next;
    }     
}

void Profile::unsharePlaylist(int playlistId) {
    /* TODO */
    Node<Playlist> *curr = playlists.getFirstNode();
    int size = playlists.getSize();
    for (int i = 0; i < size; i++) {
        if (curr->data.getPlaylistId() == playlistId) {
            curr->data.setShared(false);
            break;
        }
        curr = curr->next;
    }      
}

bool Profile::operator==(const Profile &rhs) const {
    return this->email == rhs.email && this->username == rhs.username && this->plan == rhs.plan;
}

bool Profile::operator!=(const Profile &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Profile &profile) {
    os << "email: " << profile.email << " |";
    os << " username: " << profile.username << " |";
    if (profile.plan == free_of_charge) {
        os << " plan: " << "free_of_charge" << " |";
    } else if (profile.plan == premium) {
        os << " plan: " << "premium" << " |";
    } else {
        os << " plan: " << "undefined" << " |";
    }

    os << " playlists: [";
    Node<Playlist> *firstPlaylistNode = profile.playlists.getFirstNode();
    Node<Playlist> *playlistNode = firstPlaylistNode;
    if (playlistNode) {
        do {
            os << playlistNode->data;
            if (playlistNode->next != firstPlaylistNode) os << ", ";
            playlistNode = playlistNode->next;
        } while (playlistNode != firstPlaylistNode);
    }
    os << "] |";
    os << " following: [";
    Node<Profile *> *firstProfileNode = profile.following.getFirstNode();
    Node<Profile *> *profileNode = firstProfileNode;
    if (profileNode) {
        do {
            os << profileNode->data->getEmail();
            if (profileNode->next != firstProfileNode) os << ", ";
            profileNode = profileNode->next;
        } while (profileNode != firstProfileNode);
    }
    os << "] |";
    os << " followers: [";
    firstProfileNode = profile.followers.getFirstNode();
    profileNode = firstProfileNode;
    if (profileNode) {
        do {
            os << profileNode->data->getEmail();
            if (profileNode->next != firstProfileNode) os << ", ";
            profileNode = profileNode->next;
        } while (profileNode != firstProfileNode);
    }
    os << "]";

    return os;
}
