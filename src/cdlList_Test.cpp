/* 
 * ------------------------------------------------------------------------
 *
 *                                   cdlList_Test.cpp
 *                                        V 0.01
 *
 *                             (c) Brian Lynch September, 2015
 *
 * ------------------------------------------------------------------------
*/

#include <cstdlib>
#include <cstdio>

#include "cdl_list.h"

// Example structure that can be stored in cdlList
struct pinfo{
   
   pinfo(){
      is_active = 0;
      particle_id = -1;
   }
   
   pinfo(const bool &active, const long int &pid){
      is_active = active;
      particle_id = pid;
   }
   
   bool is_active;                        //!< particle activity flag
   long int particle_id;                  //!< particle ID number
   
}; //!<Structure used to store all information related to particle.

/**********************************************************************************/
int main(){
printf("BEGIN main\n");


   class cdlList<struct pinfo> Tlist;
   struct pinfo data;

   // Populate test data
   for(long int i = 0; i < 10; ++i){
      data = {true,i};
      Tlist.push_back(data);
   }
   
   // Test prefix iterator
   printf("---Testing prefix iteration in for loop---\n");
   printf("Total #   Activity Counter   Particle ID\n");
   for(cdlList<struct pinfo>::iterator itr = Tlist.begin(); itr != Tlist.end();
                                                                           ++itr){
      printf("%7d %12d %10ld\n", Tlist.count, itr->data.is_active,
                                           itr->data.particle_id);
   }
   
   // Test postfix iterator
   printf("---Testing postfix iteration in for loop---\n");
   printf("Total #   Activity Counter   Particle ID\n");
   for(cdlList<struct pinfo>::iterator itr = Tlist.begin(); itr != Tlist.end();
                                                                           itr++){
      printf("%7d %12d %10ld\n", Tlist.count, itr->data.is_active, 
                                           itr->data.particle_id);
   }
   
   // Test begin() iterator
   printf("---Testing begin() iterator method---\n");
   printf("Total #   Activity Counter   Particle ID\n");
   cdlList<struct pinfo>::iterator itr1 = Tlist.begin();
   printf("%7d %12d %10ld\n", Tlist.count, itr1->data.is_active, itr1->data.particle_id);
   
   // Test insert_before() and insert_after()
   printf("---Testing insert on either side of the 3rd node---\n");
   printf("Total #   Activity Counter   Particle ID\n");
   ++itr1;
   itr1++;
   data = {true,12l};
   Tlist.insert_before(itr1,data);
   data = {true,23l};
   Tlist.insert_after(itr1,data);
   for(cdlList<struct pinfo>::iterator itr = Tlist.begin(); itr != Tlist.end();
                                                                          itr++){
      printf("%7d %12d %10ld\n", Tlist.count,itr->data.is_active,itr->data.particle_id);
   }
   
   // Test erase()
   printf("---Testing erase on either side of the 3rd node---\n");
   printf("Total #   Activity Counter   Particle ID\n");
   Tlist.erase(--itr1);
   Tlist.erase(++(++itr1));
   for(cdlList<struct pinfo>::iterator itr = Tlist.begin(); itr != Tlist.end();
                                                                           itr++){
      printf("%7d %12d %10ld\n", Tlist.count,itr->data.is_active,itr->data.particle_id);
   }
   
   // Test end() iterator
   printf("---Testing end() iterator method---\n");
   printf("Total #   Activity Counter   Particle ID\n");
   itr1 = --Tlist.end();
   printf("%7d %12d %10ld\n", Tlist.count, itr1->data.is_active, itr1->data.particle_id);

   // Test pop_back() and pop_front()
   printf("---Testing pop_back() and pop_front()---\n");
   printf("Total #   Activity Counter   Particle ID\n");
   Tlist.pop_back();
   Tlist.pop_front();
   for(cdlList<struct pinfo>::iterator itr = Tlist.begin(); itr != Tlist.end();
                                                                           itr++){
      printf("%7d %12d %10ld\n", Tlist.count, itr->data.is_active, itr->data.particle_id);
   }
   
   //Test clear
   printf("---Testing clear()---\n");
   Tlist.clear();
   printf("# nodes remaining (should be just root node): %d\n",Tlist.count);
   
   
printf("END main\n");
}