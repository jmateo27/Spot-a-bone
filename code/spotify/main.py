import webbrowser
import spotipy
import spotipy.util as util
from NFCTAGURIMAPPING import getURI

from pprint import pprint
import sys

scope = 'user-top-read user-library-read user-library-modify user-read-private playlist-modify-public user-modify-playback-state user-read-playback-state user-read-currently-playing'
username = 'justinmateo'
device_id='9d93ab7410f767104aa6d4df88f5b02b074f3814'

token = util.prompt_for_user_token(username, scope)

if token:
    sp = spotipy.Spotify(auth=token)

sp.transfer_playback(device_id=device_id, force_play=True)

if (sp.current_user()):
    print(f"Current User: {sp.current_user()['id']}")
    
else:
    print("Need an active session")
    sys.exit()
pprint(sp.current_playback())
print(f"Currently Playing: {sp.current_playback()['item']['name']}")

while True:
    print("SPOT-A-BONE running on:" + sp.current_user()['display_name'])
    print("0 - Exit")
    print("1 - Search for a Song")
    print("2 - Read From NFC")
    choice = int(input("choice: "))

    if choice == 1:
        search_song = input("Enter the song name: ")
        results = sp.search(search_song, 1, 0, "track")
        song_items = results['tracks']['items']
        song_name = song_items[0]['name']
        song_artist = song_items[0]['artists'][0]['name']
        song_id = song_items[0]['id']
        song_uri = song_items[0]['uri']
        uris = list()
        uris.append(song_uri)
        sp.start_playback(uris=uris)
        # sp.add_to_queue(song_id) # if you want to add
        print(f"Playing {song_name} by {song_artist} on {sp.current_user()['id']} {sp.current_playback()['device']['name']}")
    elif choice == 2:
        uris=list()
        with open('NFC.txt') as f:
            for line in f:
                uris.append(getURI(str(line.strip())))
        if len(uris) > 0:
            sp.start_playback(uris=uris)
        open("NFC.txt", "w").close()
    elif choice == 0:
        print("Good Bye, Have a great day!")
        break
    else:
        print("Please enter valid user-input.")
