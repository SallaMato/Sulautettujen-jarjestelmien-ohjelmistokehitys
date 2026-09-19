#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "TimeParser.h"

// time format: HHMMSS (6 characters)
int time_parse(char *time) {

	//Tarkistetaan, ettei osoitin ole null
	if (time == NULL) {
		return TIME_ARRAY_ERROR;
	}
	// Tarkistetaan, että pituus on tasan 6 merkkiä
	if (strlen(time) !=6) {
		return TIME_LEN_ERROR;
	}
	//Tarkistetaan, että kaikki merkit on numeroita
	for (int i = 0; i < 6; i++) {
		if (!isdigit(time[i])) {
			return TIME_LEN_ERROR;
		}
	}

	// TODO: Check that string is not null

	// Parse values from time string
	// For example: 124033 -> 12hour 40min 33sec
    int values[3];
	values[2] = atoi(time+4); // seconds
	time[4] = 0;
	values[1] = atoi(time+2); // minutes
	time[2] = 0;
	values[0] = atoi(time); // hours
	
	//Rajatarkistukset
	if (values[0] < 0 || values[0] > 23 ||
		values[1] < 0 || values[1] > 59 ||
		values[2] < 0 || values[2] > 59) {
			return TIME_VALUE_ERROR;
		}
	//Puretaan minuutit ja sekunnit ja palautetaan sekunteina
	int seconds = (values[1] * 60) + values [2];

	return seconds;
}

int sequence_parse(const char *seq) {
    // 1. Tarkistetaan ettei ole tyhjä osoitin
    if (seq == NULL) return SEQ_NULL_ERROR;
    
    int len = strlen(seq);
    if (len == 0) return SEQ_FORMAT_ERROR;

    // 2. Haetaan ensimmäinen kirjain (väri/komento)
    char color = seq[0];
    
    // Tarkistetaan onko komento sallittu
    if (color != 'R' && color != 'Y' && color != 'G' && color != 'T' && color != 'D') {
        return SEQ_COLOR_ERROR;
    }

    // 3. Valokomentojen (R, Y, G) pitää sisältää pilkku ja aika
    if (color == 'R' || color == 'Y' || color == 'G') {
        // Pituuden pitää olla vähintään 3 (esim. "R,1") ja toisen merkin pitää olla pilkku
        if (len < 3 || seq[1] != ',') {
            return SEQ_FORMAT_ERROR;
        }

        // Tarkistetaan, että kaikki merkit pilkun jälkeen ovat numeroita
        for (int i = 2; i < len; i++) {
            if (!isdigit(seq[i])) {
                return SEQ_TIME_ERROR;
            }
        }

        // Tarkistetaan, ettei aika ole nolla
        int time_val = atoi(seq + 2);
        if (time_val <= 0) {
            return SEQ_TIME_ERROR;
        }
    }

    return SEQ_OK;
}