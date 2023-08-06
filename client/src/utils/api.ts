import axios from 'axios';

const api = axios.create({
  headers: {
    'Content-Type': 'application/json',
    // 'Content-Type': 'multipart/form-data',
    // Accept: 'application/json',
    'X-Requested-With': 'XMLHttpRequest',
    'Access-Control-Allow-Origin': '*',
    'X-CSRF-TOKEN': document.querySelector('meta[name="csrf-token"]')?.getAttribute('content') || '',
  },
});

export default api;
