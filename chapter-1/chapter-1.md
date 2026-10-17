# Chapter 1: a tour of computer systems

## problem 1.1

Suppose you work as a truck driver, and you have been hired to carry a load of
potatoes from Boise, Idaho, to Minneapolis, Minnesota, a total distance of 2,500
kilometers. You estimate you can average 100 km/hr driving within the speed
limits, requiring a total of 25 hours for the trip



A) You hear on the news that Montana has just abolished its speed limit, which
constitutes 1,500 km of the trip. Your truck can travel at 150 km/hr. What
will be your speedup for the trip?

S = 1 / (1 - 0.6) + 0.6 / 1.5

S = 1.25X



B) You can buy a new turbocharger for your truck at www.fasttrucks.com. They
stock a variety of models, but the faster you want to go, the more it will cost.
How fast must you travel through Montana to get an overall speedup for
your trip of 1.67×?

1.67 = 1 / (1 - 0.6) + 0.6/ k

1 / 1.67 = (1 - 0.6) + 0.6 /k

0.59880 = 0.4 + 0.6/k

k = 3

The answer is 300kmh.


## problem 1.2

A car manufacturing company has promised their customers that the next release
of a new engine will show a 4× performance improvement. You have been assigned the task of delivering on that promise. You have determined that only 90%
of the engine can be improved. How much (i.e., what value of k) would you need
to improve this part to meet the overall performance target of the engine?

4X = 1 / (1 - 0.9) + 0.9 / k

k = 6
