#ifdef _WIN32
#include <windows.h>
#include <setupapi.h>
#include <wincrypt.h>
#endif

#include <stdio.h>

#ifdef _WIN32

// Função para verificar se o driver do token Certisign está instalado

#define DRIVER_NAME "Certisign"
#define SOFTWARE_NAME "Certisign"
#define CERTIFICATE_STORE "MY"

// Função para verificar se o driver do token Certisign está instalado
int VerificarDriverToken() {
    HDEVINFO hDevInfo;
    SP_DEVINFO_DATA DeviceInfoData;
    BOOL foundDriver = FALSE;

    hDevInfo = SetupDiGetClassDevs(NULL, NULL, NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
    if (hDevInfo == INVALID_HANDLE_VALUE) {
        return 0; // Erro ao obter os dispositivos
    }

    DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
    for (DWORD i = 0; SetupDiEnumDeviceInfo(hDevInfo, i, &DeviceInfoData); i++) {
        char deviceName[1024];
        if (SetupDiGetDeviceRegistryProperty(hDevInfo, &DeviceInfoData, SPDRP_DEVICEDESC, NULL, (PBYTE)deviceName, sizeof(deviceName), NULL)) {
            if (strstr(deviceName, DRIVER_NAME)) {
                foundDriver = TRUE;
                break;
            }
        }
    }

    SetupDiDestroyDeviceInfoList(hDevInfo);

    return foundDriver;
}

// Função para verificar se o software Certisign está instalado
int VerificarCertisignSoftware() {
    HKEY hKey;
    LONG result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall", 0, KEY_READ, &hKey);
    if (result != ERROR_SUCCESS) {
        return 0; // Erro ao acessar o registro
    }

    char buffer[1024];
    DWORD bufferSize;
    int foundSoftware = 0;

    for (DWORD i = 0; ; i++) {
        bufferSize = sizeof(buffer);
        result = RegEnumKeyEx(hKey, i, buffer, &bufferSize, NULL, NULL, NULL, NULL);
        if (result != ERROR_SUCCESS) {
            break; // Nenhum software encontrado ou fim da lista
        }

        HKEY hSoftwareKey;
        if (RegOpenKeyEx(hKey, buffer, 0, KEY_READ, &hSoftwareKey) == ERROR_SUCCESS) {
            bufferSize = sizeof(buffer);
            if (RegQueryValueEx(hSoftwareKey, "DisplayName", NULL, NULL, (LPBYTE)buffer, &bufferSize) == ERROR_SUCCESS) {
                if (strstr(buffer, SOFTWARE_NAME)) {
                    foundSoftware = 1;
                    RegCloseKey(hSoftwareKey);
                    break;
                }
            }
            RegCloseKey(hSoftwareKey);
        }
    }

    RegCloseKey(hKey);
    return foundSoftware;
}

// Função para verificar se o certificado digital está instalado
int VerificarCertificadoDigital() {
    HCERTSTORE hCertStore = CertOpenStore(CERT_STORE_PROV_SYSTEM, 0, 0, CERT_SYSTEM_STORE_CURRENT_USER, CERTIFICATE_STORE);
    if (hCertStore == NULL) {
        return 0; // Erro ao abrir o repositório de certificados
    }

    PCCERT_CONTEXT pCertContext = NULL;
    int foundCert = 0;
    pCertContext = CertFindCertificateInStore(hCertStore, X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, 0, CERT_FIND_ANY, NULL, pCertContext);

    if (pCertContext != NULL) {
        foundCert = 1;
        CertFreeCertificateContext(pCertContext);
    }

    CertCloseStore(hCertStore, CERT_CLOSE_STORE_FORCE_FLAG);

    return foundCert;
}

// Função principal que realiza as verificações
int main() {
    printf("Verificando as dependências do token A3 Certisign...\n");

    if (VerificarDriverToken()) {
        printf("Driver do token Certisign encontrado.\n");
    } else {
        printf("Driver do token Certisign não encontrado. Por favor, instale o driver.\n");
    }

    if (VerificarCertisignSoftware()) {
        printf("Software Certisign encontrado.\n");
    } else {
        printf("Software Certisign não encontrado. Por favor, instale o software.\n");
    }
    if (VerificarCertificadoDigital()) {
        printf("Certificado digital encontrado no repositório.\n");
    } else {
        printf("Nenhum certificado digital encontrado. Por favor, instale o certificado.\n");
    }
    return 0;
}

#endif // _WIN32
