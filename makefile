restaurantWaitlist.o: restaurantWaitlist.c restuarantWaitlist.h
		gcc -c restaurantWaitlist.c
waitlistlinkedListFunctions.o: waitlistlinkedListFunctions.c restaurantWaitlist.h
		gcc -c waitlistlinkedListFunctions.c
waitlistlinkedListImplementation.o: waitlistlinkedListImplementation.c restaurantWaitlist.h
		gcc -c waitlistlinkedListImplementation.c
