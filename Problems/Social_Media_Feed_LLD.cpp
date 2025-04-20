// 🚀 Question: Design and Implement a Mini Social Media Feed System
// 🧩 Problem Statement:
// You are required to implement a simplified version of a social media platform, similar to Twitter. The system should support the following features:

// Post a Message

// Delete a Message

// Follow a User

// Unfollow a User

// Get Feed

// 🧑‍💻 Functional Requirements:
// Every user can post a message (each post has a unique ID and a timestamp).

// A user can delete any of their own posts.

// A user can follow or unfollow other users.

// A user can fetch their feed, which should return up to 10 of the most recent posts made by themselves and the users they follow, sorted by most recent first.

// 🧾 Input Format:
// Each line of input represents one operation. You must continue reading input until EOF.

// txt
// Copy
// Edit
// post <userId> <postId>
// delete <userId> <postId>
// follow <followerId> <followeeId>
// unfollow <followerId> <followeeId>
// feed <userId>
// 📤 Output Format:
// For feed <userId>, print up to 10 most recent posts (most recent first) as space-separated post IDs.

// For other operations, print nothing.

// 🧪 Sample Input:
// txt
// Copy
// Edit
// post Alice 101
// post Bob 201
// post Alice 102
// follow Alice Bob
// feed Alice
// unfollow Alice Bob
// feed Alice
// delete Alice 101
// feed Alice
// 🎯 Sample Output:
// txt
// Copy
// Edit
// 201 102 101
// 102
// 102
// 🧠 Constraints & Notes:
// Assume post timestamps increase with each new post command (you can use an incrementing global counter to simulate this).

// Each postId is unique and created only once.

// A user cannot follow themselves.

// Deleting a post that doesn’t exist or doesn’t belong to the user should have no effect.

// Use efficient data structures so that feed fetches are fast even with many users/posts.

// ✅ Evaluation Criteria:
// Correctness of all functionalities

// OOP Design: meaningful classes and data encapsulation

// Code readability and modularity

// Time and space efficiency

#include <bits/stdc++.h>
using namespace std;

int timer = 0;

class User {
private:
    string userID;
    unordered_set<string> following;

public:
    User(string uid) : userID(uid) {}

    string getUserID() const {
        return userID;
    }

    unordered_set<string>& getFollowing() {
        return following;
    }

    void follow(string otherID) {
        if (otherID != userID) {
            following.insert(otherID);
        }
    }

    void unfollow(string otherID) {
        following.erase(otherID);
    }
};

class SocialMedia {
private:
    map<int, pair<string, int>> timeMap; // time -> (userID, postID)

public:
    void addPost(int postID, string userID) {
        timeMap[timer++] = {userID, postID};
    }

    void deletePost(int postID) {
        for (auto it = timeMap.begin(); it != timeMap.end(); ++it) {
            if (it->second.second == postID) {
                timeMap.erase(it);
                break;
            }
        }
    }

    vector<int> showTopTen(User* user) {
        unordered_set<string> following = user->getFollowing();
        following.insert(user->getUserID()); // include user's own posts

        vector<int> res;
        for (auto it = timeMap.rbegin(); it != timeMap.rend(); ++it) {
            if (following.count(it->second.first)) {
                res.push_back(it->second.second);
                if (res.size() == 10) break;
            }
        }
        return res;
    }
};

int main() {
    unordered_map<string, User*> users;
    SocialMedia* sm = new SocialMedia();

    cout << "Commands:\n";
    cout << "  post <userID> <postID>\n";
    cout << "  delete <postID>\n";
    cout << "  follow <followerID> <followeeID>\n";
    cout << "  unfollow <followerID> <followeeID>\n";
    cout << "  feed <userID>\n";
    cout << "  exit\n\n";

    string input;
    while (getline(cin, input)) {
        if (input == "exit") break;

        stringstream ss(input);
        string cmd;
        ss >> cmd;

        if (cmd == "post") {
            string uid;
            int pid;
            ss >> uid >> pid;

            if (!users.count(uid)) users[uid] = new User(uid);
            sm->addPost(pid, uid);
            cout << "Post added by " << uid << ": " << pid << "\n";

        } else if (cmd == "delete") {
            int pid;
            ss >> pid;
            sm->deletePost(pid);
            cout << "Post deleted: " << pid << "\n";

        } else if (cmd == "follow") {
            string u1, u2;
            ss >> u1 >> u2;
            if (!users.count(u1)) users[u1] = new User(u1);
            if (!users.count(u2)) users[u2] = new User(u2);
            users[u1]->follow(u2);
            cout << u1 << " followed " << u2 << "\n";

        } else if (cmd == "unfollow") {
            string u1, u2;
            ss >> u1 >> u2;
            if (users.count(u1)) {
                users[u1]->unfollow(u2);
                cout << u1 << " unfollowed " << u2 << "\n";
            }

        } else if (cmd == "feed") {
            string uid;
            ss >> uid;
            if (!users.count(uid)) {
                cout << "User not found.\n";
                continue;
            }
            vector<int> feed = sm->showTopTen(users[uid]);
            cout << "Feed for " << uid << ": ";
            for (int postID : feed) cout << postID << " ";
            cout << "\n";

        } else {
            cout << "Invalid command.\n";
        }
    }

    // Cleanup
    for (auto& pair : users) {
        delete pair.second;
    }
    delete sm;

    return 0;
}
