#pragma once
#include <Arduino.h>

// Created 2026/03/02 19:38:09
// Updated for Dual Architecture (AVR/ESP32) Support - English Version
// ------------------------------------------
// ID  | Category Name    | Words
// ----|------------------|----------
//  0  | PRONOUNS         |     33
//  1  | PLACES           |     26
//  2  | HOUSE            |     51
//  3  | VERBS            |     51
//  4  | ADJECTIVES       |     61
//  5  | NAMES            |     42
//  6  | TIME             |     40
//  7  | OBJECTS          |     41
//  8  | CAUSES OF DEATH  |     36
// ------------------------------------------

// Use PROGMEM to ensure strings are stored in Flash memory on AVR
const char p0[] PROGMEM = "PRONOUNS/I/You/He/She/It/We/You/They/My/Your/His/Her/Our/Someone/No one/All/One/Everyone/Who/What/Man/Woman/Child/Girl/Boy/Mother/Father/Brother/Sister/Stranger/Guest/Enemy";
const char p1[] PROGMEM = "PLACES/Here/There/Up/Down/Left/Right/Front/Back/Near/Far/Outside/Inside/Between/Behind/Under/Beside/Opposite/Everywhere/Nowhere/Middle/Corner/Away/Back/Deep/High";
const char p2[] PROGMEM = "HOUSE/Cellar/Attic/Hallway/Room/Kitchen/Bathroom/Bedroom/Stairs/Cabinet/Mirror/Window/Door/Wall/Floor/Garden/Forest/Grave/Cemetery/Church/Chapel/Tower/Ruin/Well/Hall/Chamber/Dungeon/Barn/Fence/Gate/Alley/Threshold/Foundation/Fireplace/Balcony/Storage/Stable/Forge/Altar/Coffin/Vault/Mausoleum/Crypt/Lab/Clinic/Asylum/Hospital/School/Prison/Bridge/Pond";
const char p3[] PROGMEM = "VERBS/Go/Run/Hide/Search/Find/Hear/See/Feel/Speak/Call/Shout/Whisper/Wait/Kill/Die/Help/Save/Bleed/Scratch/Knock/Open/Close/Burn/Freeze/Shiver/Breathe/Watch/Follow/Disappear/Appear/Touch/Warn/Hate/Suffer/Pray/Sacrifice/Dig/Hit/Throw/Move/Pull/Push/Come/Stay/Flee/Protect/Watch/Heal/Destroy/Remember";
const char p4[] PROGMEM = "ADJECTIVES/Cold/Hot/Dark/Light/Old/Evil/Good/Lonely/Abandoned/Sad/Angry/Hungry/Sick/Dead/Alive/Weak/Strong/Silent/Loud/Cruel/Hidden/Pure/Impure/Pale/Heavy/Light/Sharp/Bitter/Rotten/Icy/Gloomy/Lost/Eternal/Holy/Cursed/Possessed/Visible/Invisible/Horrible/Terrible/Watchful/Mute/Blind/Deaf/Wet/Dry/Old-fashioned/Modern/Broken/Whole/Safe/Dangerous/Somber/Musty/Foggy/Bloody/Festering/Sticky/Gentle/Wild";
const char p5[] PROGMEM = "NAMES/Adolf/Albert/Andreas/Anna/August/Berta/Carl/Christian/Dorothea/Elisabeth/Emil/Emma/Friedrich/Georg/Gertrud/Hans/Heinrich/Helene/Hermann/Ida/Jakob/Johann/Johanna/Joseph/Karl/Katharina/Ludwig/Margarethe/Maria/Martha/Otto/Paul/Peter/Richard/Rosa/Rudolf/Sophie/Thomas/Ursula/Walter/Wilhelm";
const char p6[] PROGMEM = "TIME/Second/Minute/Hour/Day/Week/Month/Year/Decade/Century/Spring/Summer/Autumn/Winter/Monday/Tuesday/Wednesday/Thursday/Friday/Saturday/Sunday/Morning/Noon/Evening/Night/Midnight/Dawn/Yesterday/Today/Tomorrow/Soon/Immediately/Never/Forever/Then/Earlier/Later/Now/Old/New";
const char p7[] PROGMEM = "OBJECTS/Knife/Book/Key/Money/Doll/Toy/Clock/Letter/Photo/Mirror/Necklace/Ring/Jewelry/Candle/Bible/Cross/Glass/Bottle/Poison/Rope/Hammer/Nail/Shovel/Lantern/Bag/Dress/Shoe/Hat/Stick/Comb/Brush/Diary/Stamp/Coin/Box/Suitcase/Chest/Rope/Chain/Lock";
const char p8[] PROGMEM = "CAUSES OF DEATH/Accident/Poison/Plague/Murder/Age/Fall/Fire/Water/Hunger/Thirst/Sickness/Fever/Pestilence/War/Shot/Blow/Stab/Betrayal/Suicide/Execution/Gallows/Axe/Anger/Revenge/Despair/Shock/Spasm/Paralysis/Suffocation/Drowning/Burning/Blood loss/Infection/Madness/Exhaustion";

// Pointer table to the strings, also stored in Flash
const char* const cat_table[] PROGMEM = {p0, p1, p2, p3, p4, p5, p6, p7, p8};

// Calculate number of categories at compile time
constexpr int NumberOfCategories = sizeof(cat_table) / sizeof(cat_table[0]);
