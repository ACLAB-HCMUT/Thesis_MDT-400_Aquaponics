import 'package:flutter/material.dart';
import 'package:shared_preferences/shared_preferences.dart';
// PAGES
import 'loginPage.dart';
import 'sensorInfo.dart';

class HomeScreen extends StatefulWidget {
  const HomeScreen({super.key});

  @override
  State<HomeScreen> createState() => HomeScreenState();
}

class HomeScreenState extends State<HomeScreen> {
  double temperature = 0.0;
  double humidity = 0.0;
  double pH = 0.0;

  @override
  void initState() {
    super.initState();
    // Simulate fetching sensor data
    fetchSensorData();
  }

  void fetchSensorData() async {
    await Future.delayed(const Duration(seconds: 2));
    // Replace this with actual sensor data fetching logic
    setState(() {
      temperature = 25.5; // Example temperature value
      humidity = 60.0;    // Example humidity value
    });
  }

  Future<void> logout() async {
    final navigator = Navigator.of(context);
    SharedPreferences preferences = await SharedPreferences.getInstance();
    preferences.remove('isLoggedIn');
    navigator.pushReplacement(
      MaterialPageRoute(builder: (context) => const LoginScreen()),
    );
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        leading: Row(
          children: [
            SizedBox(width: 16), // Adjust spacing if necessary
            Icon(Icons.menu),
            SizedBox(width: 16), // Adjust spacing if necessary
          ],
        ),
        title: Container(
          width: 200,
          height: 50,
          child: ElevatedButton(
            onPressed: () {
            },
            child: Row(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                Icon(Icons.energy_savings_leaf),
                SizedBox(width: 16), // Adjust spacing if necessary
                Text('Aquaponics', style: TextStyle(fontSize: 20),),
              ],
            ),
          ),
        ),
        centerTitle: true,
        actions: [
          IconButton(
            icon: const Icon(Icons.logout),
            onPressed: () {
              // Handle search action
              logout();
            },
          ),
        ],
      ),

      body: Padding(
        padding: const EdgeInsets.all(16.0),
        child: Container(
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              Expanded(
                child: const Placeholder(),
              ),
              Expanded(
                child: Row(
                    children: [
                      Expanded(
                        child: Container(
                          child: const Placeholder(),
                        ),
                      ),
                      Expanded(
                        child: Container(
                          color: Colors.grey[25],
                          child: Column(
                            mainAxisAlignment: MainAxisAlignment.center,
                            children: [
                              SensorInfo(
                                name: 'Temperature',
                                value: '$temperature °C',
                                icon: Icons.thermostat,
                                color: Colors.blue,
                                isConnected: true,
                              ),
                              SensorInfo(
                                  name: 'Humidity',
                                  value: '$humidity %',
                                  icon: Icons.water_drop,
                                  color: Colors.green,
                                  isConnected: true
                              ),
                              SensorInfo(
                                  name: 'pH',
                                  value: '$pH pH',
                                  icon: Icons.pie_chart,
                                  color: Colors.red,
                                  isConnected: true
                              )
                            ],
                          ),
                        ),
                      ),
                    ]
                ),
              ),
              Expanded(
                child: const Placeholder(),
              ),
            ],
          )
        ),
      ),
    );
  }
}