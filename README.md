# BTD6 AI TRUST

- very very basic algorithm (honestly sorta even brute force to some part) to try to beat btd6
- inspired by b2b studio's video about 3 years ago
- Hopefully it works eventually
- First actual big cpp project

## This is a personal project done on my free time because I thought it'd be very interesting
- So far I need to actually make the ai make decisions
- Most complicated math I've used is multiplication (not even division yet)
- me when above average challenging project is above average challenging
- guyss i had to mod btd6 to reliably get game data to feed to this thing
- yeah probaly will also link the btd6 mod (questionably made???) i made soon^tm
- what's an if statement
- I will try to make some goofy ahh youtube video about this just like b2b but std::err motivation not found
- I have this habit of writign random ass life stories in my code i would rather yall not look for them



### Little bit of technical implementation

**Q: How does this "AI" learn??**  
- Alright so the way this machine is able to "learn" (can machines actually learn?) is using a **genetic algorithm** based on the games it plays  
- Quick Summary of a Genetic Algorithm -> Pretty much tries a bunch of shit and see which ones do the best, and then makes variations of the best, until it succeeds/fails forever

**Q: How does this thing read and know what happens in game?**  
- unlike b2b i have a massive skill issue and am unable to directly read from ram so i just created a little mod using the help of melonloader that pretty much writes to a json file to be read by this jumble of code.  
- but like honestly what i did is kinda prone to bugs so I will 100% need to fix it a little bit hahahahaha... (im going insane) but yes
- I will UPPLOAD the mod when Im DONE TRUST...

**Q: How does it decide what random new stuff to try?**  
- I have 800 hours in BTD6 (I need to socialize with people in the flesh) and I just let it be more prone to choose certain upgrades that are costlier when rounds are later and vice versa during early rounds,  
- this is also unsupervised type learning (IM PRETTY SURE) so like i kinda want it to randomly try shit and then learn for itself
