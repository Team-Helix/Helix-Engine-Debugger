#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<unistd.h>

void cpuMonitor();
void gpuMonitor();
void appMonitor();

int choice = 0;

int main() {
	int quit = 0;
	system("clear");
	while(quit != 1) {
		printf("[HELIX-ENGINE DEBUGGER]\n");
		printf("1) Monitor App\n");
		printf("2) Monitor CPU\n");
		printf("3) Monitor GPU\n");
		printf("4) Exit\n");
		printf("\n");
		printf("Enter an option: ");
		choice = fgetc(stdin);
		while(fgetc(stdin) != '\n');
		switch(choice) {
			case '1':
				system("clear");
				appMonitor();
				break;
			case '2':
				system("clear");
				cpuMonitor();
				break;
			case '3':
				system("clear");
				gpuMonitor();
				break;
			case '4':
				system("clear");
				quit = 1;
				break;
			default:
				system("clear");
				break;
		}
	}
	return 0;
}

void appMonitor() {
	printf("[HELIX-ENGINE APP MONITOR]\n\n");
	system("adb logcat HelixEngine:D *:S");
}

void cpuMonitor() {
	printf("Choose the CPU configuration your device has:\n");
	printf("1) Octa-core big.LITTLE ARM64\n");
	printf("2) Quad-core big.LITTLE ARM64\n");
	printf("3) Single Clustered/32-bit ARM\n");
	printf("Enter a choice: ");
	choice = fgetc(stdin);

	while(true) {
		system("clear");
		printf("[HELIX-ENGINE CPU MONITOR]\n\n");
		printf("GOVERNOR: ");
		system("adb shell cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor");
		printf("CPU0 MAX: ");
		system("adb shell cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq");
		printf("CPU0 MIN: ");
		system("adb shell cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_min_freq");

		switch(choice) {
			case '1':
				printf("CPU4 MAX: ");
				system("adb shell cat /sys/devices/system/cpu/cpufreq/policy4/scaling_max_freq");
				printf("CPU4 MIN: ");
				system("adb shell cat /sys/devices/system/cpu/cpufreq/policy4/scaling_min_freq");
				break;
			case '2':
				printf("CPU2 MAX: ");
				system("adb shell cat /sys/devices/system/cpu/cpu2/cpufreq/scaling_max_freq");
				printf("CPU2 MIN: ");
				system("adb shell cat /sys/devices/system/cpu/cpu2/cpufreq/scaling_min_freq");
				break;
			case '3':
				break;
			default:
				break;
		}

		sleep(5);
	}
}

void gpuMonitor() {
	int choice2 = 0;
	char path[128];
	char buffer[128];
	printf("Choose your chipset:\n");
	printf("1) MSM8998\n");
	printf("2) MSM8996/PRO\n");
	printf("3) Kirin 970\n");
	printf("Enter a choice: ");
	choice = fgetc(stdin);

	switch(choice) {
		case '1':
			strcpy(path, "/sys/devices/soc/5000000.qcom,kgsl-3d0/devfreq/5000000.qcom,kgsl-3d0");
			break;

		case '2':
			strcpy(path, "/sys/devices/soc/b00000.qcom,kgsl-3d0/devfreq/b00000.qcom,kgsl-3d0");
			break;

		case '3':
			strcpy(path, "/sys/class/devfreq/gpufreq/subsystem/gpufreq");
			break;

		default:
			break;
	}

	while(true) {
		system("clear");
		printf("[HELIX-ENGINE GPU MONITOR]\n\n");

		printf("GPU MAX: ");
		snprintf(buffer, sizeof(buffer), "adb shell su -c cat %s/max_freq", path);
		system(buffer);

		printf("GPU MIN: ");
		snprintf(buffer, sizeof(buffer), "adb shell su -c cat %s/min_freq", path);
		system(buffer);

		sleep(5);
	}
}
