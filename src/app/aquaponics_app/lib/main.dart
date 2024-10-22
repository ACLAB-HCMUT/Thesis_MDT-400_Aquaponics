import 'package:flutter/material.dart';
import 'package:shared_preferences/shared_preferences.dart';
// PAGES
import 'package:aquaponics_app/homePage.dart';
import 'package:aquaponics_app/loginPage.dart';

void main() async {
  final isLoggedIn = await getLoginStatus();
  runApp(MyApp(isLoggedIn: isLoggedIn));
}

Future<bool> getLoginStatus() async {
  SharedPreferences preferences = await SharedPreferences.getInstance();
  return preferences.getBool('isLoggedIn') ?? false;
}

class MyApp extends StatelessWidget {
  final bool isLoggedIn;
  const MyApp({super.key, required this.isLoggedIn});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Aquaponics App',
      theme: ThemeData.light(),
      darkTheme: ThemeData.dark(),
      themeMode: ThemeMode.system,
      initialRoute: '/login',
      home : isLoggedIn ? const HomeScreen() : const HomeScreen(),
    );
  }
}