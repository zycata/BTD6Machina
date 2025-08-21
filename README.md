# BTD6 AI 

- Algorithm using genetic evolution learning to learn how to play the game
- inspired by b2b studio's video about 3 years ago


# FlowChart & include hierarchy below

<img width="1920" height="1080" alt="Image" src="https://github.com/user-attachments/assets/4be4b520-ddb0-4b02-be17-e75336d3e701" />




## This is a personal project done on my free time because I thought it'd be very interesting
- So far I need to actually make the ai make decisions
- Most complicated math I've used is multiplication (not even division yet)
- me when above average challenging project is above average challenging
- guyss i had to mod btd6 to reliably get game data to feed to this thing
- yeah probaly will also link the btd6 mod (questionably made???) i made soon^tm
- what's an if statement
- I have this habit of writign random ass life stories in my code i would rather yall not look for them



### Little bit of technical implementation

**Q: How does this "AI" learn??**  
- Alright so the way this machine is able to "learn" (can machines actually learn?) is using a **genetic algorithm** based on the games it plays  
- Quick Summary of a Genetic Algorithm -> Pretty much tries a bunch of shit and see which ones do the best, and then makes variations of the best, until it succeeds/fails forever

**Q: How does this thing read and know what happens in game?**  
- Being unable to read from the ram, or that process being extremely difficult, I created a mod with melonloader to effectively be able interpret game values.
- This works by sending out json files periodically to update the AI on what's happening.

**Q: How does it decide what random new stuff to try?**  
- I have 800 hours in BTD6  and I just let it be more prone to choose certain upgrades that are costlier when rounds are later and vice versa during early rounds, 
- this is also unsupervised type learning (IM PRETTY SURE) so like i kinda want it to randomly try shit and then learn for itself

**Q: Will a video be made on this?**
- yes yes yes yes im putting this to remind me to do that i have a bunch of clips in davinci and will hopefully finish that soon
- unfortunately im not too familiar with davinci i used to use kapwing and some capcut but those now have a watermark for free use
