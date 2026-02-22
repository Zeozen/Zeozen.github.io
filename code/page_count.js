// // page_count.js
// const SUPABASE_URL = 'https://ndbofiopsoyvouktgyej.supabase.co';
// const SUPABASE_KEY = 'sb_publishable_snLWhTe434QNCoZKAnUB3Q_xpvVD7PQ';
// const supabaseClient = supabase.createClient(SUPABASE_URL, SUPABASE_KEY);

// const counterEl = document.getElementById('visit-counter');

// async function initCounter() {
//   try {
//     let { data: row, error: selectError } = await supabaseClient
//       .from('page_visit_counter')
//       .select('value')
//       .eq('id', 1)
//       .single();

//     let count = row?.value ?? 0;

//     let { data: rpcData, error: rpcError } = await supabaseClient
//       .rpc('increment_page_visit_counter');

//     if (!rpcError) 
//     {
//         count = rpcData;
//     }

//     if (counterEl) counterEl.textContent = count;

//   } catch (err) {
//     console.error(err);
//   }
// }

// document.addEventListener('DOMContentLoaded', initCounter);

// page_count.js
const SUPABASE_URL = 'https://ndbofiopsoyvouktgyej.supabase.co';
const SUPABASE_KEY = 'sb_publishable_snLWhTe434QNCoZKAnUB3Q_xpvVD7PQ';
const supabaseClient = supabase.createClient(SUPABASE_URL, SUPABASE_KEY);

const counterEl = document.getElementById('visit-counter');

async function initCounter() {
  try {
    // increment only once per session
    if (!sessionStorage.getItem('visited')) {
      await supabaseClient.rpc('increment_page_visit_counter');
      sessionStorage.setItem('visited', '1');
    }

    // fetch current counter value
    const { data: row, error } = await supabaseClient
      .from('page_visit_counter')
      .select('value')
      .eq('id', 1)
      .single();

    if (error) console.warn('Fetch error:', error);

    if (counterEl) counterEl.textContent = row?.value ?? 0;

  } catch (err) {
    console.error('Unexpected error:', err);
  }
}

document.addEventListener('DOMContentLoaded', initCounter);