/*
ServiceQueue.h
J
Type
C
Size
7 KB (6,749 bytes)
Storage used
0 bytesOwned by undefined
Location
src
Owner
Jacob Sanchez
Modified
Feb 17, 2019 by Jacob Sanchez
Opened
10:27 PM by me
Created
Feb 26, 2019
No description
Viewers can download
*/
#ifndef _SERVICE_QUEUE_H
#define _SERVICE_QUEUE_H

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>


class ServiceQueue {

  private:
        /** Your private data members here!
        *   (you should have NO PUBLIC data members!
        *
        * Nested private types also go here.
        * For example, if your design needs some kind of
        *   structure, you would specify it here.
        */
      enum Service{//Determines if in queue or stack
        QUEUE,
        BUZZER_BUCKET
        };
      //Queue Nodes
      struct QueueNodes {
  		  QueueNodes *next;
        QueueNodes *prev;
        int buzzer_ID;
        Service location;
  		  QueueNodes(int _buzzer_ID,QueueNodes* _prev=nullptr,QueueNodes* _next=nullptr,Service _location=QUEUE){
  			  buzzer_ID = _buzzer_ID; prev = _prev;next = _next;location = _location;
  		  }
  	  };
      QueueNodes *front;
      QueueNodes *back;
      int buzzer_counter;
      //Buzzer stack
      struct Buzzer_bucket{
        QueueNodes *top;
        int buzzer_bucket_size = 0;
      };
      Buzzer_bucket buzzer_bucket;
      //Vector which holds addresses of QueueNodes
      std::vector<QueueNodes*> buzzer_address;
      /*Checks if stack is empty*/
      bool isEmpty(){
        if(buzzer_bucket.top == nullptr)
          return true;
        else
          return false;
      }
/*
      int push_buzzer_bucket(QueueNodes *push_front){
        //Non empty Stack
        if(!isEmpty()){
          push_front = front;//SeatNode
          front = front->next;
          front->prev = nullptr;
          push_front->next = buzzer_bucket.top;//Add to the stack
          buzzer_bucket.top->prev = push_front;//Already doing it
          buzzer_bucket.top = push_front;
        }
        //Empty Stack
        else{
          buzzer_bucket.top = front;
          front = front->next;
          buzzer_bucket.top->next = nullptr; //// Adjust next pointer of top
        }
        buzzer_bucket.buzzer_bucket_size++;//Adjust stack size
        return buzzer_bucket.top->buzzer_ID;
      }
      */
      void push_buzzer_bucket(QueueNodes *push_front){
        if(!isEmpty()){
          push_front->next = buzzer_bucket.top;//Add to the stack
          buzzer_bucket.top->prev = push_front;//Already doing it
          buzzer_bucket.top = push_front;
        }
        //Empty Stack
        else{
          buzzer_bucket.top = push_front;
          buzzer_bucket.top->next = nullptr; //// Adjust next pointer of top
        }
        buzzer_bucket.top->location = BUZZER_BUCKET;//Adjust Location
        buzzer_bucket.top->prev = nullptr;//Make stack prev pointer null
        buzzer_bucket.buzzer_bucket_size++;//Adjust stack size
      }
  public:

	/**
	 * Constructor
	 * Description: intializes an empty service queue.
	 *
	 * RUNTIME REQUIREMENT: O(1)
	 *
         * TODO
	 */
         ServiceQueue() {
           front = back = nullptr;
           buzzer_counter = 0;
         }
	/**
	 * Destructor
	 * Description:  deallocates all memory assciated
	 *   with service queue
	 *
	 * RUNTIME REQUIREMENT:  O(N_b) where N_b is the number of buzzer
	 *	IDs that have been used during the lifetime of the
	 *	service queue; in general, at any particular instant
	 *	the actual queue length may be less than N_b.
	 *
	 *	[See discussion of "re-using buzzers" below]
	 *
         * TODO
	 */
	~ServiceQueue() {
    //Delete Queue
    QueueNodes *tmp;
    while(front!=nullptr){
      tmp = front->next;
      free(front);
      front = tmp;
    }
    //Delete stack
    while(buzzer_bucket.top!=nullptr){
      tmp = buzzer_bucket.top->next;
      free(buzzer_bucket.top);
      buzzer_bucket.top = tmp;
    }
        }
/*
pop from the queue_size
Add to the stack
*/
  /*
    int dequeue(){
      //Adjust Queue
      //May fail at empty list case
      QueueNodes* tmp = front;
      front = front->next;
      //Adjust stack
      tmp->next = buzzer_bucket.top;
      buzzer_bucket.top = tmp;
      free(tmp);
      buzzer_bucket.buzzer_bucket_size++;
      return buzzer_bucket.top->buzzer_ID;
    }

    int enqueue(){
      //Add to the end of the Queue
      QueueNodes *newBuzzer = new QueueNodes(buzzer_counter,back,nullptr);
      back = newBuzzer;
    }
    */
    /**
  	 * Function: length()
  	 * Description:  returns the current number of
  	 *    entries in the queue.
  	 *
  	 * RUNTIME REQUIREMENT:  O(1)
  	 */
  	int  length() {
      return buzzer_counter - buzzer_bucket.buzzer_bucket_size;
          }
	/**
	 * Function: snapshot()
         * param:  buzzers is an integer vector passed by ref
	 * Description:  populates buzzers vector with a "snapshot"
         *               of the queue as a sequence of buzzer IDs
         *
	 *
	 * RUNTIME REQUIREMENT:  O(N)  (where N is the current queue
	 *		length).
	 */
	void snapshot(std::vector<int> &buzzers) {
          buzzers.clear();   // you don't know the history of the
                                //   buzzers vector, so we had better
                                //   clear it first.
          //Traverse through address vector
          QueueNodes *snap = front;
          while(snap!=nullptr){
            buzzers.push_back(snap->buzzer_ID);
            snap = snap->next;
          }
        }
	/**
	 * Function: give_buzzer()
         * Return:   buzzer-ID (integer) assigned to the new customer.
	 * Description:  This is the "enqueue" operation.  For us
	 *    a "buzzer" is represented by an integer (starting
	 *    from zero).  The function selects an available buzzer
	 *    and places a new entry at the end of the service queue
	 *    with the selected buzer-ID.
	 *    This buzzer ID is returned.
	 *    The assigned buzzer-ID is a non-negative integer
	 *    with the following properties:
	 *
	 *       (1) the buzzer (really it's ID) is not currently
	 *         taken -- i.e., not in the queue.  (It
	 *         may have been in the queue at some previous
	 *         time -- i.e., buzzer can be re-used).
	 *	  This makes sense:  you can't give the same
	 *	  buzzer to two people!
	 *
	 *       (2) Reusable Buzzers:  A re-usable buzzer is
	 *	  a buzzer that _was_ in the queue at some previous
	 *	  time, but currently is not.
	 *
         *         REQUIREMENT:  If there is one or more reusable
         *         buzzer, you MUST return one of them; furthermore,
         *         it must be the buzzer that became reusable most
         *         MOST RECENTLY.
	 *
	 *       (3) if there are no previously-used / reusable buzzers,
         *         the SMALLEST possible buzzer-ID is used (retrieved from
         *         inventory).
	 *	    Properties in this situation (where N is the current
	 *	      queue length):
	 *
	 *		- The largest buzzer-ID used so far is N-1
	 *
	 *		- All buzzer-IDs in {0..N-1} are in the queue
	 *			(in some order).
	 *
	 *		- The next buzzer-ID (from the basement) is N.
	 *
	 *    In other words, you can always get more buzzers (from
	 *    the basement or something), but you don't fetch an
	 *    additional buzzer unless you have to (i.e., no reusable buzzers).
	 *
	 * Comments/Reminders:
	 *
	 *	Rule (3) implies that when we start from an empty queue,
	 *	the first buzzer-ID will be 0 (zero).
	 *
	 *	Rule (2) does NOT require that the _minimum_ reuseable
	 *	buzzer-ID be used.  If there are multiple reuseable buzzers,
	 *	any one of them will do.
	 *
	 *	Note the following property:  if there are no re-useable
	 *	buzzers, the queue contains all buzzers in {0..N-1} where
	 *       N is the current queue length (of course, the buzzer IDs
	 *	may be in any order.)
	 *
	 * RUNTIME REQUIREMENT:  O(1)  ON AVERAGE or "AMORTIZED"
	 *          In other words, if there have been M calls to
	 *		give_buzzer, the total time taken for those
	 *		M calls is O(M).
	 *
	 *		An individual call may therefore not be O(1) so long
	 *		as when taken as a whole they average constant time.
	 *
	 */
  //Adjust give buzzer accordingly
	int  give_buzzer() {
    ///Check if stack is empty
    if(!isEmpty()){
      //Non Empty Queue
      if(front != nullptr){
        back->next = buzzer_bucket.top;
        back->next->prev = back;//Adjusting new back to point to old back
        buzzer_bucket.top = buzzer_bucket.top->next;
        back = back->next;
        back->next = nullptr;
        back->location = QUEUE;
      }
      //Empty Queue
      else{
        front = buzzer_bucket.top;
        back = front;
        buzzer_bucket.top = buzzer_bucket.top->next;//Adjust new top of stack
        front->next = nullptr;
        front->prev = nullptr;
        front->location = QUEUE;//Change location of buzzer
      }
      buzzer_bucket.buzzer_bucket_size--;//Adjust stack size
      return front->buzzer_ID;
    }
    //Stack is empty
    else{
        QueueNodes* newBuzzer = new QueueNodes(buzzer_counter,back);
        buzzer_counter++;//Adjusted after
        //Checks for empty Queue
        if(front == nullptr){
          front = newBuzzer;
          back = front;
        }
        ///Non Empty Queue
        else{
           back->next = newBuzzer;
           back = newBuzzer;
        }
      buzzer_address.push_back(newBuzzer);///store new node
      return buzzer_counter - 1;
    }
        }
	/**
	 * function: seat()
	 * description:  if the queue is non-empty, it removes the first
	 *	 entry from (front of queue) and returns the
	 *	 buzzer ID.
	 *	 Note that the returned buzzer can now be re-used.
	 *
	 *	 If the queue is empty (nobody to seat), -1 is returned to
	 *	 indicate this fact.
         *
         * Returns:  buzzer ID of dequeued customer, or -1 if queue is empty.
	 *
	 * RUNTIME REQUIREMENT:  O(1)
	 */
	int seat() {
    //Empty Queue
    if(front==nullptr)
      return -1;
    //Non empty Queue
    else{
      //Non empty Stack
      QueueNodes *tmp = front;//SeatNode
      if(front==back){//Single Node in Queue case
        front = back = nullptr;
      }
      else{
        front = front->next;
        front->prev = nullptr;
      }
      push_buzzer_bucket(tmp);//Push to stack
      return buzzer_bucket.top->buzzer_ID;
    }//End of Non empty Queue Case
        }
  /*
  Find function

  bool find(int buzzer){
    return std::find(snapshot.begin(),snapshot.end(),buzzer) != snapshot.end();
  }
  */
  /*
  remove function
  */
  /*
  bool remove(int buzzer){
    if(queueAddress[buzzer] != nullptr){
      QueueNodes *tmp = queueAddress[buzzer];
      tmp->prev->next = tmp->next;
      free(tmp);
      return true;
    }
    else
      return false;
  }
  */
	/**
	 * function: kick_out()
	 *
	 * description:  Some times buzzer holders cause trouble and
	 *		a bouncer needs to take back their buzzer and
	 *		tell them to get lost.
	 *
	 *		Specifially:
	 *
	 *		If the buzzer given by the 2nd parameter is
	 *		in the queue, the buzzer is removed (and the
	 *		buzzer can now be re-used) and 1 (one) is
	 *		returned (indicating success).
	 *
	 * Return:  If the buzzer isn't actually currently in the
	 *		queue, the queue is unchanged and false is returned
	 *		(indicating failure).  Otherwise, true is returned.
	 *
	 * RUNTIME REQUIREMENT:  O(1)
	 */
	bool kick_out(int buzzer) {
    if(buzzer_address[buzzer] == nullptr || buzzer_address[buzzer]->location == BUZZER_BUCKET || front==nullptr)//front==nullptr
      return false;
    else{
      //Kick out in middle
      QueueNodes *kickout = buzzer_address[buzzer];
      if(kickout->prev != nullptr && kickout->next != nullptr){
        kickout->prev->next = kickout->next;//Adjust queue
        kickout->next->prev = kickout->prev;
      }
      //Kick out is at the back
      else if(kickout == back && front!=back){
        back = back->prev;
        back->next = nullptr;
      }
      //Kick out is front in list more than one
      else if(kickout == front && front!=back){
        front = front->next;
        front->prev = nullptr;
      }
      //Kick out at front and only one
      else{
        front = back = nullptr;
      }
      //Return to the stack
      push_buzzer_bucket(kickout);
      return true;
    }
        }
	/**
	 * function:  take_bribe()
	 * description:  some people just don't think the rules of everyday
	 *		life apply to them!  They always want to be at
	 *		the front of the line and don't mind bribing
	 *		a bouncer to get there.
	 *
	 *	        In terms of the function:
	 *
	 *		  - if the given buzzer is in the queue, it is
	 *		    moved from its current position to the front
	 *		    of the queue.  1 is returned indicating success
	 *		    of the operation.
	 *		  - if the buzzer is not in the queue, the queue
	 *		    is unchanged and 0 is returned (operation failed).
	 *
	 * Return:  If the buzzer isn't actually currently in the
	 *		queue, the queue is unchanged and false is returned
	 *		(indicating failure).  Otherwise, true is returned.
	 *
	 * RUNTIME REQUIREMENT:  O(1)
	 */
	bool take_bribe(int buzzer) {
    //Buzzer not in queue
      if(buzzer_address[buzzer] == nullptr || buzzer_address[buzzer]->location==BUZZER_BUCKET)
        return false;
      //buzzer in queue
      else {///NEED METHOD TO CONFIRM EXIST in QUEUE not just exist
        kick_out(buzzer);
        QueueNodes *bribe = buzzer_bucket.top;
        buzzer_bucket.top = buzzer_bucket.top->next;
        buzzer_bucket.buzzer_bucket_size--;//Adjust size of bucket
        if(buzzer_bucket.top != nullptr)//SingleNode case in stack
          buzzer_bucket.top->prev = nullptr;
        //Push stack top into front of queue
        if(front!=nullptr){
          bribe->next = front;
          front->prev = bribe;
          front = bribe;
        }
        else{///front=nullptr
          bribe->next = nullptr;
          bribe->prev = nullptr;//Might not be needed
          front = back = bribe;
        }
        //bribe->prev = nullptr;//Might not be needed
        front->location = QUEUE;
        return true;
      }
};   // end ServiceQueue class


};
#endif
