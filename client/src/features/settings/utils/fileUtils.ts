const downloadURL = function (data: string, fileName: string) {
  const a: HTMLAnchorElement = document.createElement('a');
  a.href = data;
  a.download = fileName;
  document.body.appendChild(a);
  a.setAttribute('style', 'display: none');
  a.click();
  a.remove();
};

export const downloadBlob = (
  data: ArrayBufferLike,
  fileName = 'spright.png',
  mimeType = 'application/octet-stream',
) => {
  const blob = new Blob([data], {
    type: mimeType,
  });
  const url = window.URL.createObjectURL(blob);
  downloadURL(url, fileName);
  setTimeout(function () {
    return window.URL.revokeObjectURL(url);
  }, 1000);
};

export const downloadString = (str: string, fileName: string) => {
  downloadURL('data:text/plain;charset=utf-8,' + encodeURIComponent(str), fileName);
};
