import 'package:flutter/material.dart';
import 'package:shared_preferences/shared_preferences.dart';
// PAGES
import 'package:aquaponics_app/loginPage.dart';

class HomeScreen extends StatefulWidget {
  const HomeScreen({super.key});

  @override
  State<HomeScreen> createState() => HomeScreenState();
} 

class HomeScreenState extends State<HomeScreen> {
  
  Future<void> logout() async {
    final navigator = Navigator.of(context);
    SharedPreferences preferences = await SharedPreferences.getInstance();
    preferences.remove('isLoggedIn');
    navigator.pushReplacement(
      MaterialPageRoute(builder: (context) => const LoginScreen())
    );
  }

  @override
  Widget build(BuildContext context) {
    return const Scaffold(

    );
  }
}