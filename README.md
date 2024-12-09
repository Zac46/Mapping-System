# Mapping System    

The galvanometer system is used for optical experiments requiring microfield scanning (such as local transmission spectrum measurements). It can achieve microfield scanning within an area of 20-30 µm, with a minimum step size for laser spot movement of approximately **0.05-0.06 µm (closer to 0.053 µm)**. The galvanometer motor has no significant backlash.

Scanning Shape: a rectangular area with length and width on the scale of tens of micrometers.

![6739a698c32b4ef74ced8945ac46ddad](https://github.com/user-attachments/assets/193e3148-b28a-499a-b0fb-e5add9e2ad9d)



Figure 1: Mapping System

1: Galvanometer (controlled by control panel which receive signal from DAC to Rotate the mirror)   


2: positioning stage where the sample is placed


<img width="444" alt="827920b08cd2234ec35a2f183649fd8b" src="https://github.com/user-attachments/assets/4643f64e-aa7a-40c6-982f-67acfff86712">

Figure 2: Mapping System

1:STM32 Microchip      

2:DAC module              

3:STLINK for downloading program into STM32       

4:USB Serial port for Controlling the Mapping System by LabVIEW Program


<img width="570" alt="8d0451e4385d26d2c07268fba696edfd" src="https://github.com/user-attachments/assets/41b8fc4c-93b3-408d-8c19-3cc15a5edfde">


<img width="570" alt="105dcc2bf224f5d5993e76a70a4fec41" src="https://github.com/user-attachments/assets/5e869c64-60ad-4706-80ce-062101bd62a9">



Figure 3&4: testing resolution/precision of  mapping system, there are about 200 steps between each testing point that were recorded


<img width="570" alt="105dcc2bf224f5d5993e76a70a4fec41" src="https://github.com/user-attachments/assets/5b9c3676-b519-4903-9a7c-39c1aa8bb675">


Figure 5: LabVIEW interface for doing Mapping and controlling the galvanometer


<img src="https://github.com/user-attachments/assets/cbd6e5d4-63e0-41ab-944f-124f45f38eb5" alt="Galvanometer and Control panel" width="500"/>


Figure 6:Galvanometer and Control panel

<img src="https://github.com/user-attachments/assets/6cae5f3e-6cb5-4db4-9798-1b380acc3270" alt="Galvanometer and Control panel" width="500"/>

Figure 7:STM32F103C8T6            

<img src="https://github.com/user-attachments/assets/598597ba-bbbc-4bbf-8d1c-7a55e6acf6c7" alt="Galvanometer and Control panel" width="500"/>

Figure 8: DAC module      

The functionality of Mapping system was then confirm by a PL scannning of Monolayer & Bilayer WSe2.

<img width="550" alt="1" src="https://github.com/user-attachments/assets/ba902c69-8bfe-43a6-831a-eb1b6b553c73">

<img width="550" alt="2" src="https://github.com/user-attachments/assets/225e178c-9b12-4bdd-98ff-7523d480152d">

Figure 9 & 10: Optical image of the device (WSe2 encapsulated by hBN)


<img width="700" alt="mapping" src="https://github.com/user-attachments/assets/0e23047e-3aeb-448d-bd06-a0aeae7f8b56">

Figure 11: Scanning area on WSe2(left pictures show the laser points on the sample to show where the scan starts and ends, which are two diagonal vertices of a rectangle) 


<img width="700" alt="7da31d14c94fa5bf9cd643d204470969" src="https://github.com/user-attachments/assets/4b5f1e4f-dfff-48b3-b772-4f097a154601">

<img width="700" alt="27829b21b146cd2c7938bd8e1545bc98" src="https://github.com/user-attachments/assets/d755f14d-7b6f-40ea-9405-9a239b4fa8a6">



Figure 12 & 13: Scanning result at a 0.5um step  


<img width="700" alt="bb2e557c0ee9368c7e2644a1adc25fc7" src="https://github.com/user-attachments/assets/89b99f98-211e-431e-a0d0-01f58fa12f3a">

<img width="700" alt="e20987d78f0ebfdd54621ae49f94fcd4" src="https://github.com/user-attachments/assets/6437559f-6bd6-42a7-90d7-d3457ab199a8">


Figure 12 & 13: Scanning result at a 0.3um step 



