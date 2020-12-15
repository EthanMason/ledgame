/* 
 * File:   sound_player.h
 * Author: ethan
 *
 * Created on October 23, 2020, 9:47 PM
 */

#ifndef SOUND_PLAYER_H
#define	SOUND_PLAYER_H

#ifdef	__cplusplus
extern "C" {
#endif
    enum sounds {start_up, music, generating, button_1, button_2, button_3, button_4};
    
    
    //24 bit address input parameter
    
    
    
    
    void play_sound(enum sounds);
    void intialize_player();
    _Bool done_playing();

#ifdef	__cplusplus
}
#endif

#endif	/* SOUND_PLAYER_H */

