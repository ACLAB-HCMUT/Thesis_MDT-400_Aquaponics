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
  double ph = 0.0;

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
        title: const Text('Home'),
        actions: [
          IconButton(
            icon: const Icon(Icons.logout),
            onPressed: logout,
          ),
        ],
      ),
      body: Padding(
        padding: const EdgeInsets.all(16.0),
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            const Text(
              'Welcome to the Home Page',
              style: TextStyle(fontSize: 24, fontWeight: FontWeight.bold),
              textAlign: TextAlign.center,
            ),
            const SizedBox(height: 20),
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
            )
          ],
        ),
      ),
    );
  }
}