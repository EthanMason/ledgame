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
    //24 bit address input parameter
    void play_sound(long long address_input,long size);
    void intialize_player();

#ifdef	__cplusplus
}
#endif

#endif	/* SOUND_PLAYER_H */

