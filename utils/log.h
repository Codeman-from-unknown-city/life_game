//
// Created by sergei on 24.11.2020.
//

#pragma once

#define log(type, format, ...) printf("[" type "] (%s: %d): " format "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#define error_log(format, ...) log("ERROR", format, ##__VA_ARGS__)
#define info_log(format, ...) log("INFO", format, ##__VA_ARGS__)
